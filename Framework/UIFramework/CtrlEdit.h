#ifndef __UI_CTRLEDIT_H__
#define __UI_CTRLEDIT_H__

#include "cocos-ext.h"
#include "MyWndObject.h"

#include "DelegateEvent.h"

enum EditInputFlag
{
	EditInputFlagErr = -1,
	EditInputFlagAll = 0,
    EditInputFlagPassword = 1
};

class CCtrlTextFieldTTF : public cocos2d::CCTextFieldTTF
{
public:
	CCtrlTextFieldTTF();
	~CCtrlTextFieldTTF();

	static CCtrlTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const cocos2d::CCSize& dimensions, cocos2d::CCTextAlignment alignment, const char *fontName, float fontSize);

	void SetInputFlag(EditInputFlag nInputFlag);
	EditInputFlag GetInputFlag() const;
	std::string GetText() const;
    void SetText(const char *pszText);

	//编辑框改变文本
	ClickEvent EventChanged;

protected:
	virtual void insertText(const char * text, int len);
	virtual void deleteBackward();

protected:
	EditInputFlag m_nInputType;
	std::string m_strText;
};


class CCtrlEdit;
class KeyboardNotificationLayer : public cocos2d::CCLayer, public cocos2d::CCIMEDelegate
{
public:
	KeyboardNotificationLayer();

	virtual std::string subtitle() = 0;
	virtual void onClickTrackNode(bool bClicked) = 0;

	virtual void registerWithTouchDispatcher();
	virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info);

	// CCLayer
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void SetWndObject(CCtrlEdit* pWnd);

protected:
	cocos2d::CCNode * m_pTrackNode;
	cocos2d::CCPoint  m_beginPos;
	CCtrlEdit* m_pWnd;
};

class CCtrlEdit : public KeyboardNotificationLayer, public cocos2d::CCTextFieldDelegate, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);

public:	
	CCtrlEdit();
	~CCtrlEdit();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlEdit);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode(); 

public:
	std::string getString();
	std::string getPlaceHolder();
	void setString(const char* pszText);
	void SetInputFlag(EditInputFlag nInputFlag);
	EditInputFlag GetInputFlag() const;
	cocos2d::CCSize GetTextSize(const char * text);

private:
	void initCursorSprite(int nHeight);

public:
	CCtrlTextFieldTTF*   m_pTextField;
protected:	
	int							m_nCharLimit;       // the textfield max char limit
	cocos2d::extension::CCScale9Sprite*			m_pCursorSprite;
	cocos2d::CCAction*			m_pCursorAction;
	cocos2d::CCPoint			m_posCursor;
    cocos2d::CCPoint            m_RecordPos;

public:
	//编辑框改变文本
	ClickEvent EventChanged;

	//结束输入(隐藏输入法)
	ClickEvent EventInputEnd;

public:
	void callbackRemoveNodeWhenDidAction(CCNode * pNode);

	// KeyboardNotificationLayer
	virtual std::string subtitle();
	virtual void onClickTrackNode(bool bClicked);

	// CCLayer
	virtual void onEnter();
	virtual void onExit();
    // CCLayer
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	// CCTextFieldDelegate
	virtual bool onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF * pSender);
	virtual bool onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF * pSender);
	virtual bool onTextFieldInsertText(cocos2d::CCTextFieldTTF * pSender, const char * text, int nLen);
	virtual bool onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF * pSender, const char * delText, int nLen);
	virtual bool onDraw(cocos2d::CCTextFieldTTF * pSender);

    virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
    virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);

	// The back key clicked
	virtual void keyBackClicked();

	// The menu key clicked. only available on wophone & android
	virtual void keyMenuClicked();

protected:
	void textChange();
	void doKeyboardShowAction();
	void doKeyboardShowDelayAction();
	void doKeyboardHideAction();

	void showKeyboard();
	void hideKeyboard();

public:
	void setOnFocus(bool bIsOnFocus);
	bool isOnFocus() const;

protected:
	cocos2d::CCIMEKeyboardNotificationInfo m_infoIMEKeyboardNotification;
};

#endif
