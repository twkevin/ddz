#include "MyDialog.h"
#include "CtrlStaticEx.h"

#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"

#include "PublicFunc.h"
#include <libxml/parser.h>

namespace
{
	const char GUI_XML[] = { "xml/language_zh.xml" };

	static xmlNodePtr getXMLNodeForKey(xmlDocPtr doc, const char* pKey, xmlNodePtr *rootNode)
	{
		xmlNodePtr curNode = NULL;

		// check the key value
		if (! pKey)
		{
			return NULL;
		}

		do 
		{
			// get root node
			*rootNode = xmlDocGetRootElement(doc);
			if (NULL == *rootNode)
			{
				CCLOG("read root node error");
				break;
			}

			// find the node
			curNode = (*rootNode)->xmlChildrenNode;
			while (NULL != curNode)
			{
				if (! xmlStrcmp(curNode->name, BAD_CAST pKey))
				{
					break;
				}

				curNode = curNode->next;
			}
		} while (0);

		return curNode;
	}
}

CCtrlStaticEx* CCtrlStaticEx::create(const char *pszText, const char *fontName, float fontSize, CCTextAlignment hAlignment, cocos2d::CCSize ScrollViewSize)
{
	CCtrlStaticEx* pScrollLabel = new CCtrlStaticEx;
	if( pScrollLabel && pScrollLabel->init( pszText, fontName, fontSize, hAlignment, ScrollViewSize ) )
	{
		pScrollLabel->autorelease();
		return pScrollLabel;
	}
	else
	{
		CC_SAFE_DELETE( pScrollLabel );
		return NULL;
	}
}

CCtrlStaticEx::CCtrlStaticEx()
	: m_nFontSize(0)
	, m_nFontColor(0)
	, m_strFontName(FONT_NAME)
	, m_strText("")
	, m_nTextAlignment(0)
	, m_nVerticalTextAlignment(0)
	, m_pScrollView( NULL )
	, m_pLabel( NULL )
{

}

CCtrlStaticEx::~CCtrlStaticEx()
{
	CC_SAFE_RELEASE_NULL( m_pLabel );
	CC_SAFE_RELEASE_NULL( m_pScrollView );
}

bool CCtrlStaticEx::init(const char *pszText, const char *fontName, float fontSize, CCTextAlignment hAlignment, cocos2d::CCSize& ScrollViewSize)
{
	//object has been initialized.
	if( m_pScrollView || m_pLabel )
	{
		return false;
	}

	//constraint the label's width, but not height.
	m_pLabel = CCLabelTTF::create( pszText, fontName, fontSize, CCSizeMake( ScrollViewSize.width, 0 ), hAlignment );
	m_pLabel->retain();

	//get the texture size
	CCSize TextSize = m_pLabel->getTexture()->getContentSize();

	//we have to invoke CCScrollView::create( ScrollViewSize ) instead of 
	//CCScrollView::create( ScrollViewSize, m_pLabel ) to let the CCScrollView
	//create a default container for you.

	//It's because that the label may smaller than the view of
	//CCScrollView. If that is the condition, the label will be positioned
	//at the bottom of the View by CCScrollView. 

	//Even though you can set the label at the top, but the behavior of
	//ScrollView always try to reposition it. So we must ensure the container
	//is larger than the View of CCScrollView.
	m_pScrollView = CCScrollView::create( ScrollViewSize );
	m_pScrollView->retain();
	m_pScrollView->setDelegate( this );
	m_pScrollView->setDirection( kCCScrollViewDirectionVertical );

	//set the container size.
	//So we must ensure the conainer is larger than the View of CCScrollView.
	if( TextSize.height > ScrollViewSize.height )
	{
		m_pScrollView->setContentSize( TextSize );
		//make the left-top corner of container coincide with View's
		m_pScrollView->setContentOffset( ccp( 0, ScrollViewSize.height - TextSize.height ) );
	}
	else
	{
		m_pScrollView->setContentSize( ScrollViewSize );
	}

	//put the label at the top of the container.
	m_pScrollView->addChild( m_pLabel );
	m_pLabel->ignoreAnchorPointForPosition( false );
	m_pLabel->setAnchorPoint( ccp( 0, 1 ) );
	m_pLabel->setPosition( ccp( 0, m_pScrollView->getContentSize().height ) );


	addChild( m_pScrollView );

	return true;
}

bool CCtrlStaticEx::init()
{
	//object has been initialized.
	if( m_pScrollView || m_pLabel )
	{
		return false;
	}

	CCSize ScrollViewSize = CCSize(m_nWidth, m_nHeight);
	m_pLabel = CCLabelTTF::create(m_strText.c_str(), m_strFontName.c_str(), m_nFontSize, CCSize(m_nWidth, 0), 
		(CCTextAlignment)m_nTextAlignment, (CCVerticalTextAlignment)m_nVerticalTextAlignment);
	m_pLabel->retain();

	CCSize TextSize = ScrollViewSize;

	//we have to invoke CCScrollView::create( ScrollViewSize ) instead of 
	//CCScrollView::create( ScrollViewSize, m_pLabel ) to let the CCScrollView
	//create a default container for you.

	//It's because that the label may smaller than the view of
	//CCScrollView. If that is the condition, the label will be positioned
	//at the bottom of the View by CCScrollView. 

	//Even though you can set the label at the top, but the behavior of
	//ScrollView always try to reposition it. So we must ensure the container
	//is larger than the View of CCScrollView.

	m_pScrollView = CCScrollView::create( ScrollViewSize );
	m_pScrollView->retain();
	m_pScrollView->setDelegate( this );
	m_pScrollView->setDirection( kCCScrollViewDirectionVertical );


	//put the label at the top of the container.
	m_pScrollView->addChild( m_pLabel );

	m_pLabel->setColor(ccGetColor3B(m_nFontColor));
	m_pLabel->setOpacity(ccGetOpacity(m_nFontColor));	

	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));	
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));

	addChild( m_pScrollView );
	
	if (!m_strText.empty())
	{
		this->setString(m_strText.c_str());
	}

	return true;
}

void CCtrlStaticEx::setString(const char* pszText)
{
	if (m_pLabel)
	{
		m_pLabel->setString(pszText);

		CCSize ScrollViewSize = CCSize(m_nWidth, m_nHeight);

		CCTexture2D* pTexture = m_pLabel->getTexture();
		if (NULL == pTexture)
		{
			m_pLabel->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
			m_pLabel->setPosition(ccp(0, m_nHeight));
			m_pScrollView->setContentSize( ScrollViewSize );

			return;
		}

		//get the texture size
		CCSize TextSize = pTexture->getContentSize();

		if( TextSize.height > ScrollViewSize.height )
		{
			m_pScrollView->setContentSize( TextSize );
			//make the left-top corner of container coincide with View's
			m_pScrollView->setContentOffset( ccp( 0, ScrollViewSize.height - TextSize.height ) );

			m_pLabel->setAnchorPoint(ccp(0, 0));
			m_pLabel->setPosition(ccp(0, 0));
		}
		else
		{
			m_pLabel->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
			m_pLabel->setPosition(ccp(0, m_nHeight));
			m_pScrollView->setContentSize( ScrollViewSize );
		}
	}
}

GLint CCtrlStaticEx::readNode()
{
	GLint nRet = CCMyWndObject::readNode();

	if (0 != nRet)
	{
		return -1;
	}

	CMyIni* pIni = g_objIniMgr.GetMyIniPtr(m_strGuiPath.c_str());

	if (NULL == pIni)
	{
		return -1;
	}

	std::string strIndex = FORMAT("%d-%d") << m_nParentWndID << m_nWndID;

	m_nFontSize = pIni->GetValue(strIndex.c_str(), "fontSize", g_nDefualtFontSize);
	m_nFontColor = pIni->GetValue(strIndex.c_str(), "fontColor", g_nDefualtFontColor);
	m_nTextAlignment = pIni->GetValue(strIndex.c_str(), "herAlign", g_nDefaultTextAlignment);
	m_nVerticalTextAlignment = pIni->GetValue(strIndex.c_str(), "verAlign", g_nDefaultVerticalTextAlignment);

	const char *pszValue = pIni->GetString(strIndex.c_str(), "text");
	if (pszValue)
	{
		const char* pszStr= g_objStrMgr.GetStr(pszValue);
		if (pszStr)
		{
			m_strText = pszStr;
		}
		else
		{
			m_strText = "";
		}
	}
	else
	{
		m_strText = "";
	}

	unsigned long ulLength = 0;
	const char* pBuffer = GetFileData(GUI_XML, "r", ulLength);
	if (NULL != pBuffer)
	{
		xmlDocPtr doc = xmlParseMemory(pBuffer, ulLength);  
		if(!doc)  
		{
			CCLOG("CCtrlStaticEx::xmlParseMemory[%s] failed", GUI_XML);
			return -1;  
		}

		std::string strkey = "text";
		strkey.append(pszValue);
		const char* ret = NULL;
		xmlNodePtr rootNode;
		xmlNodePtr node = getXMLNodeForKey(doc, strkey.c_str(), &rootNode);

		// find the node
		if (node)
		{
			ret = (const char*)xmlNodeGetContent(node);
		}

		if (ret)
		{
			m_strText = ret;
		}
	}	

	return 0;
}

GLint CCtrlStaticEx::initGUI()
{
	GLint nRet = this->readNode();

	if (!init())
	{
		return -1;
	}

	return nRet;
}

bool CCtrlStaticEx::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlStaticEx::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isVisible() || IsMsgThrough())
	{
		return NULL;
	}

	return this;
}