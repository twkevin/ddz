--
-- DlgSmallGamePage.lua
--
require("lua/object")

DlgSmallGamePage = {}

local obj = {
		nDialogIDD = 407,
		myDlg = nil,
		btnFirGame = nil,
		btnSecGame = nil,
		pageNum = nil,
    }
        

function DlgSmallGamePage:create()
    
    if nil ~= obj.myDlg then
        return obj
    end
    
    obj = newObject(obj, DlgSmallGamePage)	
	obj.myDlg = CCMyDialog:newDlg(obj.nDialogIDD)
	--obj.myDlg:setVisible(true)
	
	local function onBtnFirGameUp()
        if nil == obj.myDlg then
        	return
        end    
		obj.myDlg:setVisible(false)	
    end		
	obj.btnFirGame = CCtrlButtonEx:create(1001, obj.myDlg)	
	obj.btnFirGame:addHandleOfControlEvent(onBtnFirGameUp,CCControlEventTouchUpInside)
	
	local function onBtnSecGameUp()	    
        if nil == obj.myDlg then
        	return
        end
		obj.myDlg:setVisible(false)        
    end
	
	obj.btnSecGame = CCtrlButtonEx:create(1002, obj.myDlg)	
	obj.btnSecGame:addHandleOfControlEvent(onBtnSecGameUp,CCControlEventTouchUpInside)
	
    return obj
end


