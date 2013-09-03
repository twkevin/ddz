--
-- DlgLogin.lua
--
require("lua/object")
require("lua/DlgGameCenter")

DlgLogin = {}

local obj = {
		nDialogIDD = 100,
		myDlg = nil,
		staText = nil,
        imgLock = nil,
		btnLogin = nil,
		btnRegister = nil,
		editUserName = nil,
		proLoading = nil,
		BMFontStatic = nil,
		chcboxPwd = nil,
		staRuleEx = nil,		
    }
    
        local function touchDownAction()
			local dlg = DlgGameCenter:create()
			if nil == dlg then
        		return
        	end			
			local hDlg = CUIManager:sharedInstancePtr():GetHandleByIDD(dlg.nDialogIDD)
			CUIManager:sharedInstancePtr():ShowDialog(hDlg, true, true)
			
        	if nil == obj.staText then
        		return
        	end       	
        	obj.staText:setString(CCString:create("Touch Down"):getCString())
        end
        
        local function touchDragInsideAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Drag Inside"):getCString())
        end
        
        local function touchDragOutsideAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Drag Outside"):getCString())
        end
        
        local function touchDragEnterAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Drag Enter"):getCString())
        end
        
        local function touchDragExitAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Drag Exit"):getCString())
        end
        
        local function touchUpInsideAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Touch Up Inside."):getCString())
        end
        
        local function touchUpOutsideAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Touch Up Outside."):getCString())
        end
        
        local function touchCancelAction()
        	if nil == obj.staText then
        		return
        	end 
        	obj.staText:setString(CCString:create("Touch Cancel"):getCString())
        end


function DlgLogin:create()
    
    if nil ~= obj.myDlg then
        return obj
    end
    
    obj = newObject(obj, DlgLogin)	
	obj.myDlg = CCMyDialog:create(obj.nDialogIDD)
	obj.myDlg:setVisible(true);	
	
	obj.staText = CCtrlStatic:create(1001, obj.myDlg)

	obj.imgLock = CCtrlImageEx:create(1004, obj.myDlg)
	--obj.imgLock:SetBgAni("btn_pwd_lock")
	obj.imgLock:setTouchEnabled(true)	
	
	obj.imgLock:addHandleOfControlEvent(touchDownAction,CCControlEventTouchDown)
    obj.imgLock:addHandleOfControlEvent(touchDragInsideAction,CCControlEventTouchDragInside)
    obj.imgLock:addHandleOfControlEvent(touchDragOutsideAction,CCControlEventTouchDragOutside)
    obj.imgLock:addHandleOfControlEvent(touchDragEnterAction,CCControlEventTouchDragEnter)
    obj.imgLock:addHandleOfControlEvent(touchDragExitAction,CCControlEventTouchDragExit)
    obj.imgLock:addHandleOfControlEvent(touchUpInsideAction,CCControlEventTouchUpInside)
    obj.imgLock:addHandleOfControlEvent(touchUpOutsideAction,CCControlEventTouchUpOutside)
    obj.imgLock:addHandleOfControlEvent(touchCancelAction,CCControlEventTouchCancel)
	
	
	local function onBtnLoginUp()
	    obj.myDlg:setVisible(false)
        if nil == obj.staText then
        	return
        end 
        --obj.staText:setVisible(false)        
    end		
	obj.btnLogin = CCtrlButtonEx:create(1005, obj.myDlg)	
	obj.btnLogin:addHandleOfControlEvent(onBtnLoginUp,CCControlEventTouchUpInside)
	
	
	local function onBtnRegisterUp()
        if nil == obj.proLoading then
        	return
        end 
        local fValue = obj.proLoading:getValue() + 0.1;
        if fValue >= 1.1 then
            fValue = 0.0
        end
	    obj.proLoading:setValue(fValue);
    end		
	obj.btnRegister = CCtrlButtonEx:create(1006, obj.myDlg)	
	obj.btnRegister:addHandleOfControlEvent(onBtnRegisterUp,CCControlEventTouchUpInside)
	
	obj.editUserName = CCtrlEdit:create(1010, obj.myDlg)
	
	obj.proLoading = CCtrlProgress:create(1100, obj.myDlg)	
	
	local fValue = obj.proLoading:getValue() + 0.5;
	obj.proLoading:setValue(fValue);
	
	obj.BMFontStatic = CCtrlBMFontStatic:create(1101, obj.myDlg)	
	
	obj.chcboxPwd = CCtrlCheckBox:create(1003, obj.myDlg)

	obj.staRuleEx = CCtrlStaticEx:create(1102, obj.myDlg)
		
	
    return obj
end


