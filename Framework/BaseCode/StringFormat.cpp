#pragma warning (disable: 4786)
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include "CQGlobal.h"

#include "StringFormat.h"


// ================================================================================================
// 常量定义 & 数据类型定义
namespace string_format
{
	// FORMAT_FLAGS：在格式串中可以设置的标记
	enum FORMAT_FLAGS
	{
		// flags
		FORCE_SIGN_FLAG			= 1 << 0,			// flags设置了“+”
		LEFT_ALIGN_FLAG			= 1 << 1,			// flags设置了“-”
		MODIFY_STYLE_FLAG		= 1 << 2,			// flags设置了“#”
		FILL_ZERO_FLAG			= 1 << 3,			// flags设置了“0”
		RESERVE_SIGN_FLAG		= 1 << 4,			// flags设置了“ ”

		// length
		SHORT_INTEGER			= 1 << 8,			// length设置为“h”
		LONG_INTEGER			= 1 << 9,			// length设置为“l”
		LONG_DOUBLE				= 1 << 10,			// length设置为“L”
		LONG64_INTEGER			= 1 << 11,			// length设置为“I64”

		// 其它
		USE_WIDTH				= 1 << 12,			// width设置为数字
		SPECIFY_WIDTH			= 1 << 13,			// width设置为“*”
		USE_PRECISION			= 1 << 14,			// precision设置为数字
		SPECIFY_PRECISION		= 1 << 15,			// precision设置为“*”
	};

	// FORMAT_DATA：格式串中需要动态替换的部分，将其格式保存在此
	// 根据C标准，可以分为四个部分，因此可用四个字段来记录。
	struct FORMAT_DATA
	{
		int						iFlags;				// 设置的标记。参见enum FORMAT_FLAGS
		char					cSpecifier;
		int						iWidth;
		int						iPrecision;
	};

	// ARG_DATA_TYPE：参数的数据类型。
	// 说明：对于C标准的printf函数，它是支持可变长参数的，在传参数时它遵守以下规则：
	//       各种带符号的“整数”类型（包括char, short, int, 各种enum等。但不包括后来才定义的long long，即__int64），在传递时全部转为long类型
	//       各种无符号的“整数”类型与之类似，在传递时全部转为unsigned long类型
	//       float类型在传递时全部转为double类型
	//       后来定义的long long（VC6的__int64）、unsigned long long（VC6的unsigned __int64）、long double，在传递时按照原样传递，不转化
	// 因此，没有必要定义出CHAR_TYPE, SHORT_TYPE, FLOAT_TYPE等，使用INTEGER_TYPE, DOUBLE_TYPE就足够。
	enum ARG_DATA_TYPE
	{
		INTEGER_TYPE		= 1,
		INT64_TYPE,
		DOUBLE_TYPE,
		LONGDOUBLE_TYPE,
		POINTER_TYPE,
		STRING_POINTER_TYPE,
		INTEGER_POINTER_TYPE,
	};

	// 参数数据。用一个struct保存一个参数。
	// 先用一个type字段表示参数的具体类型，然后无论是什么类型，其具体的数据都放在一个union之中。
	struct ARG_DATA
	{
		ARG_DATA_TYPE	type;
		union {
			long		integerData;
			__int64		int64Data;
			double		doubleData;
			long double	longDoubleData;
			const void*	pointerData;
			const char*	stringPointerData;
			int*		integerPointerData;
		};
	};
}

// ================================================================================================
// 错误处理
namespace string_format
{
	ErrorHandler s_ErrorHandler = NULL;

	void SetErrorHandler(ErrorHandler handler)
	{
		s_ErrorHandler = handler;
	}

	ErrorHandler GetErrorHandler()
	{
		return s_ErrorHandler;
	}

	void s_DefaultErrorHandler(ErrorCode err, const char* pszMessage)
	{
		// do nothing, but assert(0)
		assert(0);
	}

	void s_RaiseError(ErrorCode err, const char* pszMessage)
	{
		ErrorHandler handler = s_ErrorHandler;
		if (!handler)
		{
			handler = s_DefaultErrorHandler;
		}

		handler(err, pszMessage);
	}
}

// ================================================================================================
// 解析格式串
namespace string_format
{
	// CFormatParser：格式串解析器
	// 这是一个没有状态的class，仅仅通过一些成员函数来进行操作。
	// 只有一个public函数。
	class CFormatParser
	{
	public:
		// 解析一个格式串。（格式串以“%”开头，具体格式参见“格式串的语法”）
		// 如果解析失败，返回-1，
		// 如果解析成功，返回解析时所读取的字符个数。
		// 解析成功时，formatData中保存了正确的解析结果。
		int Parse(const char* pszFormat, FORMAT_DATA& formatData) const;

	private:
		// 解析flags部分。
		// 参数说明、返回值说明与Parse函数相同。
		// 由于flags部分是可以缺省的，因此返回值可能为零
		int ParseFlags(const char* pszFormat, FORMAT_DATA& formatData) const;

		// 解析width部分。
		// 参数说明、返回值说明与Parse函数相同。
		// 由于width部分是可以缺省的，因此返回值可能为零
		int ParseWidth(const char* pszFormat, FORMAT_DATA& formatData) const;

		// 解析precision部分。
		// 参数说明、返回值说明与Parse函数相同。
		// 由于precision部分是可以缺省的，因此返回值可能为零
		int ParsePrecision(const char* pszFormat, FORMAT_DATA& formatData) const;

		// 解析length部分。
		// 参数说明、返回值说明与Parse函数相同。
		// 由于length部分是可以缺省的，因此返回值可能为零
		int ParseLength(const char* pszFormat, FORMAT_DATA& formatData) const;
	};

	int CFormatParser::Parse(const char* pszFormat, FORMAT_DATA& formatData) const
	{
		if (!pszFormat || *pszFormat != '%')
		{
			return -1;
		}

		memset(&formatData, 0, sizeof(formatData));

		int iOffset = 1;
		int iResult;

		iResult = ParseFlags(pszFormat + iOffset, formatData);
		iOffset += iResult;
		if (iResult < 0)
		{
			return -1;
		}

		iResult = ParseWidth(pszFormat + iOffset, formatData);
		iOffset += iResult;
		if (iResult < 0)
		{
			return -1;
		}

		iResult = ParsePrecision(pszFormat + iOffset, formatData);
		iOffset += iResult;
		if (iResult < 0)
		{
			return -1;
		}

		iResult = ParseLength(pszFormat + iOffset, formatData);
		iOffset += iResult;
		if (iResult < 0)
		{
			return -1;
		}

		switch (pszFormat[iOffset])
		{
		case 'c':
		case 'd':	case 'u':	case 'i':	case 'o':	case 'x':	case 'X':
		case 'f':	case 'e':	case 'E':	case 'g':	case 'G':
		case 'p':	case 's':	case 'n':
			formatData.cSpecifier = pszFormat[iOffset];
			++iOffset;
			return iOffset;
		default:
			return -1;
		}
	}

	int CFormatParser::ParseFlags(const char* pszFormat, FORMAT_DATA& formatData) const
	{
		for (int iOffset = 0; ; ++iOffset)
		{
			switch (pszFormat[iOffset])
			{
			case '+':
				formatData.iFlags |= FORCE_SIGN_FLAG;
				break;
			case '-':
				formatData.iFlags |= LEFT_ALIGN_FLAG;
				break;
			case '#':
				formatData.iFlags |= MODIFY_STYLE_FLAG;
				break;
			case '0':
				formatData.iFlags |= FILL_ZERO_FLAG;
				break;
			case ' ':
				formatData.iFlags |= RESERVE_SIGN_FLAG;
				break;
			default:
				return iOffset;
			}
		}
	}

	int CFormatParser::ParseWidth(const char* pszFormat, FORMAT_DATA& formatData) const
	{
		char c = *pszFormat;
		if (c == '*')
		{
			formatData.iFlags |= SPECIFY_WIDTH;
			return 1;
		}
		else if (c >= '0' && c <= '9')
		{
			formatData.iFlags |= USE_WIDTH;
			int iWidth = 0;
			for (int iOffset = 0; ; ++iOffset)
			{
				c = pszFormat[iOffset];
				if (c >= '0' && c <= '9')
				{
					iWidth *= 10;
					iWidth += (c - '0');
				}
				else
				{
					formatData.iWidth = iWidth;
					return iOffset;
				}
			}
		}

		return 0;
	}

	int CFormatParser::ParsePrecision(const char* pszFormat, FORMAT_DATA& formatData) const
	{
		char c = *pszFormat;
		if (c != '.')
		{
			return 0;
		}

		int iOffset = 1;
		c = pszFormat[iOffset];

		if (c == '*')
		{
			formatData.iFlags |= SPECIFY_PRECISION;
			return 2;
		}
		else if (c >= '0' && c <= '9')
		{
			formatData.iFlags |= USE_PRECISION;
			int iPrecision = 0;
			for (; ; ++iOffset)
			{
				c = pszFormat[iOffset];
				if (c >= '0' && c <= '9')
				{
					iPrecision *= 10;
					iPrecision += (c - '0');
				}
				else
				{
					formatData.iPrecision = iPrecision;
					return iOffset;
				}
			}
		}

		return 0;
	}

	int CFormatParser::ParseLength(const char* pszFormat, FORMAT_DATA& formatData) const
	{
		char c = *pszFormat;
		switch (c)
		{
		case 'h':
			formatData.iFlags |= SHORT_INTEGER;
			return 1;
		case 'l':
			formatData.iFlags |= LONG_INTEGER;
			return 1;
		case 'L':
			formatData.iFlags |= LONG_DOUBLE;
			return 1;
		case 'I':
			if (strncmp(pszFormat, "I64", 3) == 0)
			{
				formatData.iFlags |= LONG64_INTEGER;
				return 3;
			}
			return 0;
		default:
			return 0;
		}
	}
}

// ================================================================================================
// 实用函数
namespace string_format
{
	// 输出正负号。
	// t: 要输出的数字
	// iFlags: 参见FORMAT_FLAGS
	// strBuf: 要输出的位置
	template <typename T>
	void s_OutputSign(T t, int iFlags, std::string& strBuf)
	{
		if (t < 0)
		{
			strBuf += '-';
		}
		else if (t > 0)
		{
			if (iFlags & RESERVE_SIGN_FLAG)
			{
				strBuf += ' ';
			}
			else if (iFlags & FORCE_SIGN_FLAG)
			{
				strBuf += '+';
			}
		}
		else
		{
			if (iFlags & RESERVE_SIGN_FLAG)
			{
				strBuf += ' ';
			}
		}
	}

	// 把数字作为字符串输出。注意：负数会先取反，再输出，不考虑符号。输出符号用s_OutputSign
	// t: 要输出的数字
	// iRadix: 进制。一般设置为8, 10, 16，分别表示八进制/十进制/十六进制
	// iPrecision: 至少要输出的数字个数。如果不足则补零
	// pDigits: 使用的数字。比如十六进制，可以传入"0123456789abcdef"或者"0123456789ABCDEF"
	// strOutput: 要输出的位置
	template <typename T>
	void s_OutputInteger(T t, int iRadix, int iPrecision, const char* pDigits, std::string& strOutput)
	{
		char szBuf[256];
		char* p = szBuf;

		if (t == 0)
		{
			*p++ = pDigits[0];
		}
		else if (t < 0)
		{
			t = -t;
		}

		while (t != 0)
		{
			*p++ = pDigits[t % iRadix];
			t /= iRadix;
		}

		const int iActualLength = p - szBuf;
		if (iPrecision > iActualLength)
		{
			strOutput.append(iPrecision - iActualLength, '0');
		}

		// VC6的std::string不支持push_back，因此下面这句无法编译
		// std::reverse_copy(szBuf, p, std::back_inserter(strBuf));
		// 改用：
		std::reverse(szBuf, p);
		strOutput.append(szBuf, p);
	}

	// 把数字作为字符串输出。
	// 与s_OutputInteger类似，但假定t一定为非负（对各种unsigned类型适用）
	template <typename T>
	void s_OutputInteger_Unsigned(T t, int iRadix, int iPrecision, const char* pDigits, std::string& strOutput)
	{
		char szBuf[256];
		char* p = szBuf;

		if (t == 0)
		{
			*p++ = pDigits[0];
		}

		while (t != 0)
		{
			*p++ = pDigits[t % iRadix];
			t /= iRadix;
		}

		const int iActualLength = p - szBuf;
		if (iPrecision > iActualLength)
		{
			strOutput.append(iPrecision - iActualLength, '0');
		}

		// VC6的std::string不支持push_back，因此下面这句无法编译
		// std::reverse_copy(szBuf, p, std::back_inserter(strBuf));
		// 改用：
		std::reverse(szBuf, p);
		strOutput.append(szBuf, p);
	}
}

// ================================================================================================
// class CStringFormatter::CImpl
// 核心实现部分
namespace string_format
{
	class CStringFormatter::CImpl
	{
	public:
		CImpl(const char* pszFormat);

		// 参见CStringFormatter::AsString
		const std::string& AsString();

		// 参见CStringFormatter::ClearArguments
		void ClearArguments();

		// 参见CStringFormatter::AddArgument
		void AddArgument_Integer(long data);
		void AddArgument_Int64(__int64 data);
		void AddArgument_Double(double data);
		void AddArgument_LongDouble(long double data);
		void AddArgument_Pointer(const void* data);
		void AddArgument_SPointer(const char* data);
		void AddArgument_IPointer(int* data);

	private:
		enum FORMAT_TYPE
		{
			STATIC_FORMAT,		// 原样输出。比如"Hello, World."输出为"Hello, World."
			DYNAMIC_FORMAT,		// 动态输出。比如"%d"有可能输出为"3025"
		};

		typedef std::vector<FORMAT_DATA>	FORMAT_DATA_VEC;
		typedef std::vector<FORMAT_TYPE>	FORMAT_TYPE_VEC;
		typedef std::vector<ARG_DATA>		ARG_DATA_VEC;
		typedef std::vector<std::string>	STRING_VEC;

		bool			m_bFormatValid;			// 格式串是否有效
		bool			m_bResultValid;			// 处理的最终结果m_strResult是否有效
		std::string		m_strFormat;			// 把pszFormat保存一份，调试时观察更加方便。没有其它用处。
		std::string		m_strResult;			// 处理的最终结果。
		FORMAT_TYPE_VEC m_vecFormatType;		// 第i个成分是动态还是静态
		FORMAT_DATA_VEC	m_vecFormatData;		// 把%d, %.2f等内容解析好，保存到此
		ARG_DATA_VEC	m_vecArgData;			// 通过AddArgument_XXX系列函数添加的内容，保存到此
		STRING_VEC		m_vecSplitedString;		// 需要原样输出的串。例如"Hello, %s!"，则这里vecSplitedString = {"Hello, ", "!"}

		// 解析格式串，返回是否解析成功（保存到m_vecFormatType, m_vecFormatData, m_vecSplitedString）。
		// 此函数其实可以反复调用，而不导致状态出错。
		// 以后可能将构造函数中的参数去掉，而把此函数变为public
		bool ParseFormatString(const char* pszFormat);

		// 根据解析好的格式串和现在输入的参数，计算最终结果（保存到m_strResult，并设置m_bResultValid）
		void CalcResult();

		// 计算一个%d或者%f的输出，并添加到strCurrent的末尾
		bool CalcFormat(const FORMAT_DATA& formatData, const ARG_DATA& arg, std::string& strCurrent);
	};

	CStringFormatter::CImpl::CImpl(const char* pszFormat)
		: m_bFormatValid(false)
		, m_bResultValid(false)
	{
		if (!ParseFormatString(pszFormat))
		{
			// 错误：解析格式串失败
			std::string strError;
			strError += "invalid format string: \"";
			strError += pszFormat;
			strError += "\"";
			s_RaiseError(Error_InvalidFormatString, strError.c_str());
		}
	}

	const std::string& CStringFormatter::CImpl::AsString()
	{
		CalcResult();
		return m_strResult;
	}

	void CStringFormatter::CImpl::ClearArguments()
	{
		m_bResultValid = false;
		m_strResult = std::string();	// VC6的std::string没有clear方法
		m_vecArgData.clear();
	}

	void CStringFormatter::CImpl::AddArgument_Integer(long data)
	{
		ARG_DATA arg;
		arg.type = INTEGER_TYPE;
		arg.integerData = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_Int64(__int64 data)
	{
		ARG_DATA arg;
		arg.type = INT64_TYPE;
		arg.int64Data = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_Double(double data)
	{
		ARG_DATA arg;
		arg.type = DOUBLE_TYPE;
		arg.doubleData = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_LongDouble(long double data)
	{
		ARG_DATA arg;
		arg.type = LONGDOUBLE_TYPE;
		arg.longDoubleData = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_Pointer(const void* data)
	{
		ARG_DATA arg;
		arg.type = POINTER_TYPE;
		arg.pointerData = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_SPointer(const char* data)
	{
		ARG_DATA arg;
		arg.type = STRING_POINTER_TYPE;
		arg.stringPointerData = data;
		m_vecArgData.push_back(arg);
	}

	void CStringFormatter::CImpl::AddArgument_IPointer(int* data)
	{
		ARG_DATA arg;
		arg.type = INTEGER_POINTER_TYPE;
		arg.integerPointerData = data;
		m_vecArgData.push_back(arg);
	}

	bool CStringFormatter::CImpl::ParseFormatString(const char* pszFormat)
	{
		m_bFormatValid = false;
		m_strFormat = std::string();	// VC6的std::string没有clear方法

		ClearArguments();
		m_vecFormatType.clear();
		m_vecFormatData.clear();
		m_vecSplitedString.clear();

		if (!pszFormat)
		{
			return false;
		}

		const char* pszFormatBegin = pszFormat;
		const char* pszFormatEnd = pszFormat + strlen(pszFormat);
		while (pszFormat < pszFormatEnd)
		{
			const char* p = strchr(pszFormat, '%');
			if (!p)
			{
				m_vecFormatType.push_back(STATIC_FORMAT);
				m_vecSplitedString.push_back(std::string(pszFormat));
				break;
			}

			if (p != pszFormat)
			{
				m_vecFormatType.push_back(STATIC_FORMAT);
				m_vecSplitedString.push_back(std::string(pszFormat, p));
				pszFormat = p;
			}

			CFormatParser parser;
			FORMAT_DATA formatData;
			int iParseResult = parser.Parse(pszFormat, formatData);
			if (iParseResult < 0)
			{
				++pszFormat;

				if (*pszFormat == '%')
				{
					m_vecFormatType.push_back(STATIC_FORMAT);
					m_vecSplitedString.push_back("%");
					++pszFormat;
				}

				continue;
			}

			pszFormat += iParseResult;
			m_vecFormatType.push_back(DYNAMIC_FORMAT);
			m_vecFormatData.push_back(formatData);
		}

		assert(m_vecFormatType.size() == m_vecSplitedString.size() + m_vecFormatData.size());

// 优化：当格式串中没有任何%时，最终结果可以直接确定
// 		if (m_vecFormatData.empty())
// 		{
// 			assert(m_vecSplitedString.size() <= 1);
// 			if (!m_vecSplitedString.empty())
// 			{
// 				m_bResultValid = true;
// 				m_strResult = m_vecSplitedString[0];
// 			}
// 			else
// 			{
// 				m_bResultValid = true;
// 				m_strResult = std::string();
// 			}
// 		}

		m_strFormat = pszFormatBegin;
		m_bFormatValid = true;
		return true;
	}

	void CStringFormatter::CImpl::CalcResult()
	{
		// 如果计算结果已经被保存到m_strResult中，则直接返回，不必另行计算
		if (m_bResultValid)
		{
			return;
		}

		// 如果格式串有错，则无法得到正确结果，直接返回
		if (!m_bFormatValid)
		{
			return;
		}

		// 临时的计算结果
		std::string strResult;

		int idxFormatData = 0;
		int idxSplitedString = 0;
		int idxArgData = 0;
		for (FORMAT_TYPE_VEC::const_iterator it = m_vecFormatType.begin(); it != m_vecFormatType.end(); ++it)
		{
			switch (*it)
			{
			case STATIC_FORMAT:
				if (idxSplitedString >= static_cast<int>(m_vecSplitedString.size()))
				{
					assert(0);	// never goes here
					return;
				}

				strResult += m_vecSplitedString[idxSplitedString];
				++idxSplitedString;
				break;
			case DYNAMIC_FORMAT:
				if (idxFormatData >= static_cast<int>(m_vecFormatData.size()))
				{
					assert(0); // never goes here
					return;
				}

				{
					FORMAT_DATA formatData = m_vecFormatData[idxFormatData];
					++idxFormatData;

					if (formatData.iFlags & SPECIFY_WIDTH)
					{
						if (idxArgData >= static_cast<int>(m_vecArgData.size()))
						{
							// 错误：传入的参数数量不足
							s_RaiseError(Error_NotEnoughArguments, "not enough arguments");
							return;
						}

						const ARG_DATA& arg = m_vecArgData[idxArgData];
						++idxArgData;

						if (arg.type != INTEGER_TYPE)
						{
							// 错误：传入的参数类型错误。需要一个整数
							s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
							return;
						}

						formatData.iFlags &= ~SPECIFY_WIDTH;
						formatData.iFlags |= USE_WIDTH;
						formatData.iWidth = arg.integerData;
					}

					if (formatData.iFlags & SPECIFY_PRECISION)
					{
						if (idxArgData >= static_cast<int>(m_vecArgData.size()))
						{
							// 错误：传入的参数数量不足
							s_RaiseError(Error_NotEnoughArguments, "not enough arguments");
							return;
						}

						const ARG_DATA& arg = m_vecArgData[idxArgData];
						++idxArgData;

						if (arg.type != INTEGER_TYPE)
						{
							// 错误：传入的参数类型错误。需要一个整数
							s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
							return;
						}

						formatData.iFlags &= ~SPECIFY_PRECISION;
						formatData.iFlags |= USE_PRECISION;
						formatData.iPrecision = arg.integerData;
					}

					if (idxArgData >= static_cast<int>(m_vecArgData.size()))
					{
						// 错误：传入的参数数量不足
						s_RaiseError(Error_NotEnoughArguments, "not enough arguments");
						return;
					}

					const ARG_DATA& arg = m_vecArgData[idxArgData];
					++idxArgData;
					if (!CalcFormat(formatData, arg, strResult))
					{
						return;
					}
				}
				break;
			default:
				assert(0);	// never goes here
				break;
			} // end of switch
		} // end of for

		if (idxArgData < static_cast<int>(m_vecArgData.size()))
		{
			// 警告：传入的参数数量过多
			s_RaiseError(Warning_TooManyArguments, "too many arguments");
		}

		// 把临时结果strResult保存为最终结果m_strResult
		// 使用swap而不使用赋值，是为了更高的效率。并且swap不会有因为内存不足而失败的可能性。
		m_strResult.swap(strResult);
		m_bResultValid = true;
	}

	bool CStringFormatter::CImpl::CalcFormat(const FORMAT_DATA& formatData, const ARG_DATA& arg, std::string& strCurrent)
	{
		std::string strBuf;

		const int iFlags = formatData.iFlags;
		const char cSpecifier = formatData.cSpecifier;

		// 根据数据类型作不同处理
		switch (cSpecifier)
		{
		case 'c':
			if (arg.type != INTEGER_TYPE)
			{
				// 错误：传入的参数类型错误。需要一个整数
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
				return false;
			}

			if (iFlags & LONG_INTEGER)
			{
				wchar_t wc = (wchar_t)arg.integerData;

				// 错误：暂时没有实现%lc
				s_RaiseError(Error_NotImplemented, "wide-char not supported yet");
				return false;
			}
			else
			{
				char c = (char)arg.integerData;
				strBuf += c;
			}

			break;
		case 's':
			if (arg.type != STRING_POINTER_TYPE)
			{
				// 错误：传入的参数类型错误。需要一个字符指针
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a string-pointer");
				return false;
			}

			if (iFlags & LONG_INTEGER)
			{
				const wchar_t* ws = (const wchar_t*)arg.stringPointerData;
				if (!ws)
				{
					ws = L"(null)";
				}

				// 错误：暂时没有实现%ls
				s_RaiseError(Error_NotImplemented, "wide-char string not supported yet");
				return false;
			}
			else
			{
				const char* s = (const char*)arg.stringPointerData;
				if (!s)
				{
					s = "(null)";
				}

				const char* s_end;

				if (iFlags & USE_PRECISION)
				{
					s_end = std::find(s, s + formatData.iPrecision, '\0');
				}
				else
				{
					s_end = s + strlen(s);
				}

				const int iActualWidth = s_end - s;
				if ((iFlags & USE_WIDTH) && formatData.iWidth > iActualWidth)
				{
					const int iFill = formatData.iWidth - iActualWidth;
					const char cFill = (formatData.iFlags & FILL_ZERO_FLAG) ? '0' : ' ';
					if (iFlags & LEFT_ALIGN_FLAG)
					{
						strCurrent.append(s, s_end);
						strCurrent.append(iFill, cFill);
					}
					else
					{
						strCurrent.append(iFill, cFill);
						strCurrent.append(s, s_end);
					}
				}
				else
				{
					strCurrent.append(s, s_end);
				}

				return true;
			}

			break;
		case 'd':
		case 'i':
		case 'o':
		case 'u':
		case 'x':
		case 'X':
			{
				if ((iFlags & LONG64_INTEGER) && arg.type != INT64_TYPE)
				{
					// 错误：传入的参数类型错误。需要一个64位整数
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a 64-bit integer");
					return false;
				}

				if (!(iFlags & LONG64_INTEGER) && arg.type != INTEGER_TYPE)
				{
					// 错误：传入的参数类型错误。需要一个整数
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
					return false;
				}

				// 对于使用了'#'的情形，为八进制/十六进制写上0, 0x, 0X
				if (iFlags & MODIFY_STYLE_FLAG)
				{
					switch (cSpecifier)
					{
					case 'o':
						strBuf += '0';
						break;
					case 'x':
						strBuf += '0';
						strBuf += 'x';
						break;
					case 'X':
						strBuf += '0';
						strBuf += 'X';
					default:
						// ignore '#' flag
						break;
					}
				}

				// 判断进制
				int iRadix;
				const char* pDigits;

				switch (cSpecifier)
				{
				case 'o':
					iRadix = 8;
					pDigits = "01234567";
					break;
				case 'x':
					iRadix = 16;
					pDigits = "0123456789abcdef";
					break;
				case 'X':
					iRadix = 16;
					pDigits = "0123456789ABCDEF";
					break;
				default:
					iRadix = 10;
					pDigits = "0123456789";
					break;
				}

				// 输出数字
				const int iPrecision = (iFlags & USE_PRECISION) ? formatData.iPrecision : -1;

				switch (cSpecifier)
				{
				case 'i':
				case 'd':
				case 'o':
					if (iFlags & LONG64_INTEGER)
					{
						s_OutputSign(arg.int64Data, iFlags, strBuf);
						s_OutputInteger(arg.int64Data, iRadix, iPrecision, pDigits, strBuf);
					}
					else if (iFlags & LONG_INTEGER)
					{
						s_OutputSign(arg.integerData, iFlags, strBuf);
						s_OutputInteger(arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					else if (iFlags & SHORT_INTEGER)
					{
						s_OutputSign((short)arg.integerData, iFlags, strBuf);
						s_OutputInteger((short)arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					else
					{
						s_OutputSign((int)arg.integerData, iFlags, strBuf);
						s_OutputInteger((int)arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					break;
				case 'u':
				case 'x':
				case 'X':
					if (iFlags & LONG64_INTEGER)
					{
						s_OutputInteger_Unsigned((unsigned __int64)arg.int64Data, iRadix, iPrecision, pDigits, strBuf);
					}
					else if (iFlags & LONG_INTEGER)
					{
						s_OutputInteger_Unsigned((unsigned long)arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					else if (iFlags & SHORT_INTEGER)
					{
						s_OutputInteger_Unsigned((unsigned short)arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					else
					{
						s_OutputInteger_Unsigned((unsigned int)arg.integerData, iRadix, iPrecision, pDigits, strBuf);
					}
					break;
				default:
					assert(0);	// never goes here
					break;
				}

				break;
			}
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
			if ((iFlags & LONG_DOUBLE) && arg.type != LONGDOUBLE_TYPE)
			{
				// 错误：传入的参数类型错误。需要一个long double
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a long double");
				return false;
			}

			if (!(iFlags & LONG_DOUBLE) && arg.type != DOUBLE_TYPE)
			{
				// 错误：传入的参数类型错误。需要一个浮点数
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a float/double");
				return false;
			}

			{
				std::ostringstream oss;

				if (iFlags & USE_WIDTH)
				{
					oss.width(formatData.iWidth);
				}

				if (iFlags & USE_PRECISION)
				{
					oss.precision(formatData.iPrecision);
				}

				if (iFlags & FORCE_SIGN_FLAG)
				{
					oss.setf(std::ios::showpos);
				}

				if (iFlags & LEFT_ALIGN_FLAG)
				{
					oss.setf(std::ios::left);
				}

				if (iFlags & FILL_ZERO_FLAG)
				{
					oss.fill('0');
				}

				if (iFlags & MODIFY_STYLE_FLAG)
				{
					oss.setf(std::ios::showpoint);
				}

				if (cSpecifier == 'E' || formatData.cSpecifier == 'G')
				{
					oss.setf(std::ios::uppercase);
				}

				if (cSpecifier == 'e' || formatData.cSpecifier == 'E')
				{
					oss.setf(std::ios::scientific);
				}

				if (cSpecifier == 'f')
				{
					oss.setf(std::ios::fixed);
				}

				if (iFlags & LONG_DOUBLE)
				{
					oss << arg.longDoubleData;
				}
				else
				{
					oss << arg.doubleData;
				}

				strBuf = oss.str();
			}

			break;
		case 'p':
			{
				const void* ptr;
				switch (arg.type)
				{
				case POINTER_TYPE:
					ptr = arg.pointerData;
					break;
				case STRING_POINTER_TYPE:
					ptr = arg.stringPointerData;
					break;
				case INTEGER_POINTER_TYPE:
					ptr = arg.integerPointerData;
					break;
				default:
					// 错误：传入的参数类型错误。需要一个指针
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a pointer");
					return false;
				}

				s_OutputInteger_Unsigned((unsigned long)ptr, 16, 8, "0123456789ABCDEF", strBuf);
			}
			break;
		case 'n':
			if (arg.type != STRING_POINTER_TYPE)
			{
				// 错误：传入的参数类型错误。需要一个int指针
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an int-pointer");
				return false;
			}

			if (arg.integerPointerData)
			{
				*(arg.integerPointerData) = (int)strCurrent.length();
			}

			return true;
		case '%':
			strBuf += '%';
			break;
		default:
			assert(0);	// never goes here
			return false;
		}

		// 填入实际数据。
		// 考虑iWidth。如果实际的字符数量少于指定的宽度，则填充。填充时要考虑对齐
		const int iActualWidth = (int)strBuf.length();
		if ((iFlags & USE_WIDTH) && formatData.iWidth > iActualWidth)
		{
			const int iFill = formatData.iWidth - iActualWidth;
			const char cFill = (formatData.iFlags & FILL_ZERO_FLAG) ? '0' : ' ';
			if (iFlags & LEFT_ALIGN_FLAG)
			{
				strCurrent.append(strBuf);
				strCurrent.append(iFill, cFill);
			}
			else
			{
				strCurrent.append(iFill, cFill);
				strCurrent.append(strBuf);
			}
		}
		else
		{
			strCurrent.append(strBuf);
		}

		return true;
	}
}

// ================================================================================================
// class CStringFormatter
namespace string_format
{
	CStringFormatter::CStringFormatter(const char* pszFormat)
		: m_pImpl(new CImpl(pszFormat))
	{
	}

	CStringFormatter::~CStringFormatter()
	{
		TRY
		{
			delete m_pImpl;
		}
		CATCH (...)
		{
			// eat all exceptions
		}
	}

	CStringFormatter::CStringFormatter(const CStringFormatter& copy)
		: m_pImpl(new CImpl(*copy.m_pImpl))
	{
	}

	CStringFormatter& CStringFormatter::operator =(const CStringFormatter& copy)
	{
		if (&copy != this)
		{
			CImpl* pOldImpl = m_pImpl;
			m_pImpl = new CImpl(*copy.m_pImpl);
			delete pOldImpl;
		}

		return *this;
	}

	const std::string& CStringFormatter::AsString() const
	{
		return m_pImpl->AsString();
	}

	void CStringFormatter::ClearArguments()
	{
		m_pImpl->ClearArguments();
	}

	void CStringFormatter::AddArgument(int data)
	{
		m_pImpl->AddArgument_Integer(data);
	}

	void CStringFormatter::AddArgument(unsigned int data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(short data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(unsigned short data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(long data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(unsigned long data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(char data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(signed char data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(unsigned char data)
	{
		m_pImpl->AddArgument_Integer((int)data);
	}

	void CStringFormatter::AddArgument(__int64 data)
	{
		m_pImpl->AddArgument_Int64(data);
	}

//	void CStringFormatter::AddArgument(unsigned __int64 data)
//	{
//		m_pImpl->AddArgument_Int64((__int64)data);
//	}

	void CStringFormatter::AddArgument(float data)
	{
		m_pImpl->AddArgument_Double((double)data);
	}

	void CStringFormatter::AddArgument(double data)
	{
		m_pImpl->AddArgument_Double(data);
	}

	void CStringFormatter::AddArgument(long double data)
	{
		m_pImpl->AddArgument_LongDouble(data);
	}

	void CStringFormatter::AddArgument(const void* data)
	{
		m_pImpl->AddArgument_Pointer(data);
	}

	void CStringFormatter::AddArgument(const char* data)
	{
		m_pImpl->AddArgument_SPointer(data);
	}

	void CStringFormatter::AddArgument(int* data)
	{
		m_pImpl->AddArgument_IPointer(data);
	}
}

// ================================================================================================
// class CFormatHelper
namespace string_format
{
	CFormatHelper::CFormatHelper(const char* pszFormat)
		: m_formatter(pszFormat)
	{
	}

	CFormatHelper::operator std::string() const
	{
		return m_formatter.AsString();
	}
}
