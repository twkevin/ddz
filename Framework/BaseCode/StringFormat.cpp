#pragma warning (disable: 4786)
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include "CQGlobal.h"

#include "StringFormat.h"


// ================================================================================================
// �������� & �������Ͷ���
namespace string_format
{
	// FORMAT_FLAGS���ڸ�ʽ���п������õı��
	enum FORMAT_FLAGS
	{
		// flags
		FORCE_SIGN_FLAG			= 1 << 0,			// flags�����ˡ�+��
		LEFT_ALIGN_FLAG			= 1 << 1,			// flags�����ˡ�-��
		MODIFY_STYLE_FLAG		= 1 << 2,			// flags�����ˡ�#��
		FILL_ZERO_FLAG			= 1 << 3,			// flags�����ˡ�0��
		RESERVE_SIGN_FLAG		= 1 << 4,			// flags�����ˡ� ��

		// length
		SHORT_INTEGER			= 1 << 8,			// length����Ϊ��h��
		LONG_INTEGER			= 1 << 9,			// length����Ϊ��l��
		LONG_DOUBLE				= 1 << 10,			// length����Ϊ��L��
		LONG64_INTEGER			= 1 << 11,			// length����Ϊ��I64��

		// ����
		USE_WIDTH				= 1 << 12,			// width����Ϊ����
		SPECIFY_WIDTH			= 1 << 13,			// width����Ϊ��*��
		USE_PRECISION			= 1 << 14,			// precision����Ϊ����
		SPECIFY_PRECISION		= 1 << 15,			// precision����Ϊ��*��
	};

	// FORMAT_DATA����ʽ������Ҫ��̬�滻�Ĳ��֣������ʽ�����ڴ�
	// ����C��׼�����Է�Ϊ�ĸ����֣���˿����ĸ��ֶ�����¼��
	struct FORMAT_DATA
	{
		int						iFlags;				// ���õı�ǡ��μ�enum FORMAT_FLAGS
		char					cSpecifier;
		int						iWidth;
		int						iPrecision;
	};

	// ARG_DATA_TYPE���������������͡�
	// ˵��������C��׼��printf����������֧�ֿɱ䳤�����ģ��ڴ�����ʱ���������¹���
	//       ���ִ����ŵġ����������ͣ�����char, short, int, ����enum�ȡ��������������Ŷ����long long����__int64�����ڴ���ʱȫ��תΪlong����
	//       �����޷��ŵġ�������������֮���ƣ��ڴ���ʱȫ��תΪunsigned long����
	//       float�����ڴ���ʱȫ��תΪdouble����
	//       ���������long long��VC6��__int64����unsigned long long��VC6��unsigned __int64����long double���ڴ���ʱ����ԭ�����ݣ���ת��
	// ��ˣ�û�б�Ҫ�����CHAR_TYPE, SHORT_TYPE, FLOAT_TYPE�ȣ�ʹ��INTEGER_TYPE, DOUBLE_TYPE���㹻��
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

	// �������ݡ���һ��struct����һ��������
	// ����һ��type�ֶα�ʾ�����ľ������ͣ�Ȼ��������ʲô���ͣ����������ݶ�����һ��union֮�С�
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
// ������
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
// ������ʽ��
namespace string_format
{
	// CFormatParser����ʽ��������
	// ����һ��û��״̬��class������ͨ��һЩ��Ա���������в�����
	// ֻ��һ��public������
	class CFormatParser
	{
	public:
		// ����һ����ʽ��������ʽ���ԡ�%����ͷ�������ʽ�μ�����ʽ�����﷨����
		// �������ʧ�ܣ�����-1��
		// ��������ɹ������ؽ���ʱ����ȡ���ַ�������
		// �����ɹ�ʱ��formatData�б�������ȷ�Ľ��������
		int Parse(const char* pszFormat, FORMAT_DATA& formatData) const;

	private:
		// ����flags���֡�
		// ����˵��������ֵ˵����Parse������ͬ��
		// ����flags�����ǿ���ȱʡ�ģ���˷���ֵ����Ϊ��
		int ParseFlags(const char* pszFormat, FORMAT_DATA& formatData) const;

		// ����width���֡�
		// ����˵��������ֵ˵����Parse������ͬ��
		// ����width�����ǿ���ȱʡ�ģ���˷���ֵ����Ϊ��
		int ParseWidth(const char* pszFormat, FORMAT_DATA& formatData) const;

		// ����precision���֡�
		// ����˵��������ֵ˵����Parse������ͬ��
		// ����precision�����ǿ���ȱʡ�ģ���˷���ֵ����Ϊ��
		int ParsePrecision(const char* pszFormat, FORMAT_DATA& formatData) const;

		// ����length���֡�
		// ����˵��������ֵ˵����Parse������ͬ��
		// ����length�����ǿ���ȱʡ�ģ���˷���ֵ����Ϊ��
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
// ʵ�ú���
namespace string_format
{
	// ��������š�
	// t: Ҫ���������
	// iFlags: �μ�FORMAT_FLAGS
	// strBuf: Ҫ�����λ��
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

	// ��������Ϊ�ַ��������ע�⣺��������ȡ����������������Ƿ��š����������s_OutputSign
	// t: Ҫ���������
	// iRadix: ���ơ�һ������Ϊ8, 10, 16���ֱ��ʾ�˽���/ʮ����/ʮ������
	// iPrecision: ����Ҫ��������ָ����������������
	// pDigits: ʹ�õ����֡�����ʮ�����ƣ����Դ���"0123456789abcdef"����"0123456789ABCDEF"
	// strOutput: Ҫ�����λ��
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

		// VC6��std::string��֧��push_back�������������޷�����
		// std::reverse_copy(szBuf, p, std::back_inserter(strBuf));
		// ���ã�
		std::reverse(szBuf, p);
		strOutput.append(szBuf, p);
	}

	// ��������Ϊ�ַ��������
	// ��s_OutputInteger���ƣ����ٶ�tһ��Ϊ�Ǹ����Ը���unsigned�������ã�
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

		// VC6��std::string��֧��push_back�������������޷�����
		// std::reverse_copy(szBuf, p, std::back_inserter(strBuf));
		// ���ã�
		std::reverse(szBuf, p);
		strOutput.append(szBuf, p);
	}
}

// ================================================================================================
// class CStringFormatter::CImpl
// ����ʵ�ֲ���
namespace string_format
{
	class CStringFormatter::CImpl
	{
	public:
		CImpl(const char* pszFormat);

		// �μ�CStringFormatter::AsString
		const std::string& AsString();

		// �μ�CStringFormatter::ClearArguments
		void ClearArguments();

		// �μ�CStringFormatter::AddArgument
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
			STATIC_FORMAT,		// ԭ�����������"Hello, World."���Ϊ"Hello, World."
			DYNAMIC_FORMAT,		// ��̬���������"%d"�п������Ϊ"3025"
		};

		typedef std::vector<FORMAT_DATA>	FORMAT_DATA_VEC;
		typedef std::vector<FORMAT_TYPE>	FORMAT_TYPE_VEC;
		typedef std::vector<ARG_DATA>		ARG_DATA_VEC;
		typedef std::vector<std::string>	STRING_VEC;

		bool			m_bFormatValid;			// ��ʽ���Ƿ���Ч
		bool			m_bResultValid;			// ��������ս��m_strResult�Ƿ���Ч
		std::string		m_strFormat;			// ��pszFormat����һ�ݣ�����ʱ�۲���ӷ��㡣û�������ô���
		std::string		m_strResult;			// ��������ս����
		FORMAT_TYPE_VEC m_vecFormatType;		// ��i���ɷ��Ƕ�̬���Ǿ�̬
		FORMAT_DATA_VEC	m_vecFormatData;		// ��%d, %.2f�����ݽ����ã����浽��
		ARG_DATA_VEC	m_vecArgData;			// ͨ��AddArgument_XXXϵ�к�����ӵ����ݣ����浽��
		STRING_VEC		m_vecSplitedString;		// ��Ҫԭ������Ĵ�������"Hello, %s!"��������vecSplitedString = {"Hello, ", "!"}

		// ������ʽ���������Ƿ�����ɹ������浽m_vecFormatType, m_vecFormatData, m_vecSplitedString����
		// �˺�����ʵ���Է������ã���������״̬����
		// �Ժ���ܽ����캯���еĲ���ȥ�������Ѵ˺�����Ϊpublic
		bool ParseFormatString(const char* pszFormat);

		// ���ݽ����õĸ�ʽ������������Ĳ������������ս�������浽m_strResult��������m_bResultValid��
		void CalcResult();

		// ����һ��%d����%f�����������ӵ�strCurrent��ĩβ
		bool CalcFormat(const FORMAT_DATA& formatData, const ARG_DATA& arg, std::string& strCurrent);
	};

	CStringFormatter::CImpl::CImpl(const char* pszFormat)
		: m_bFormatValid(false)
		, m_bResultValid(false)
	{
		if (!ParseFormatString(pszFormat))
		{
			// ���󣺽�����ʽ��ʧ��
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
		m_strResult = std::string();	// VC6��std::stringû��clear����
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
		m_strFormat = std::string();	// VC6��std::stringû��clear����

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

// �Ż�������ʽ����û���κ�%ʱ�����ս������ֱ��ȷ��
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
		// ����������Ѿ������浽m_strResult�У���ֱ�ӷ��أ��������м���
		if (m_bResultValid)
		{
			return;
		}

		// �����ʽ���д����޷��õ���ȷ�����ֱ�ӷ���
		if (!m_bFormatValid)
		{
			return;
		}

		// ��ʱ�ļ�����
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
							// ���󣺴���Ĳ�����������
							s_RaiseError(Error_NotEnoughArguments, "not enough arguments");
							return;
						}

						const ARG_DATA& arg = m_vecArgData[idxArgData];
						++idxArgData;

						if (arg.type != INTEGER_TYPE)
						{
							// ���󣺴���Ĳ������ʹ�����Ҫһ������
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
							// ���󣺴���Ĳ�����������
							s_RaiseError(Error_NotEnoughArguments, "not enough arguments");
							return;
						}

						const ARG_DATA& arg = m_vecArgData[idxArgData];
						++idxArgData;

						if (arg.type != INTEGER_TYPE)
						{
							// ���󣺴���Ĳ������ʹ�����Ҫһ������
							s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
							return;
						}

						formatData.iFlags &= ~SPECIFY_PRECISION;
						formatData.iFlags |= USE_PRECISION;
						formatData.iPrecision = arg.integerData;
					}

					if (idxArgData >= static_cast<int>(m_vecArgData.size()))
					{
						// ���󣺴���Ĳ�����������
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
			// ���棺����Ĳ�����������
			s_RaiseError(Warning_TooManyArguments, "too many arguments");
		}

		// ����ʱ���strResult����Ϊ���ս��m_strResult
		// ʹ��swap����ʹ�ø�ֵ����Ϊ�˸��ߵ�Ч�ʡ�����swap��������Ϊ�ڴ治���ʧ�ܵĿ����ԡ�
		m_strResult.swap(strResult);
		m_bResultValid = true;
	}

	bool CStringFormatter::CImpl::CalcFormat(const FORMAT_DATA& formatData, const ARG_DATA& arg, std::string& strCurrent)
	{
		std::string strBuf;

		const int iFlags = formatData.iFlags;
		const char cSpecifier = formatData.cSpecifier;

		// ����������������ͬ����
		switch (cSpecifier)
		{
		case 'c':
			if (arg.type != INTEGER_TYPE)
			{
				// ���󣺴���Ĳ������ʹ�����Ҫһ������
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
				return false;
			}

			if (iFlags & LONG_INTEGER)
			{
				wchar_t wc = (wchar_t)arg.integerData;

				// ������ʱû��ʵ��%lc
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
				// ���󣺴���Ĳ������ʹ�����Ҫһ���ַ�ָ��
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

				// ������ʱû��ʵ��%ls
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
					// ���󣺴���Ĳ������ʹ�����Ҫһ��64λ����
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a 64-bit integer");
					return false;
				}

				if (!(iFlags & LONG64_INTEGER) && arg.type != INTEGER_TYPE)
				{
					// ���󣺴���Ĳ������ʹ�����Ҫһ������
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect an integer");
					return false;
				}

				// ����ʹ����'#'�����Σ�Ϊ�˽���/ʮ������д��0, 0x, 0X
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

				// �жϽ���
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

				// �������
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
				// ���󣺴���Ĳ������ʹ�����Ҫһ��long double
				s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a long double");
				return false;
			}

			if (!(iFlags & LONG_DOUBLE) && arg.type != DOUBLE_TYPE)
			{
				// ���󣺴���Ĳ������ʹ�����Ҫһ��������
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
					// ���󣺴���Ĳ������ʹ�����Ҫһ��ָ��
					s_RaiseError(Error_InvalidArgumentType, "invalid argument type. expect a pointer");
					return false;
				}

				s_OutputInteger_Unsigned((unsigned long)ptr, 16, 8, "0123456789ABCDEF", strBuf);
			}
			break;
		case 'n':
			if (arg.type != STRING_POINTER_TYPE)
			{
				// ���󣺴���Ĳ������ʹ�����Ҫһ��intָ��
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

		// ����ʵ�����ݡ�
		// ����iWidth�����ʵ�ʵ��ַ���������ָ���Ŀ�ȣ�����䡣���ʱҪ���Ƕ���
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
