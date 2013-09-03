--
-- DlgGameCenter.lua
--
require("lua/object")
require("lua/DlgSmallGamePage")

DlgGameCenter = {}

local obj = {
		nDialogIDD = 406,
		myDlg = nil,
		btnLeft = nil,
		btnRight = nil,
		pageSGames = nil,
		btnReturn = nil,		
    }    
        

function DlgGameCenter:create()
    
    if nil ~= obj.myDlg then
        return obj
    end
    
    obj = newObject(obj, DlgGameCenter)	
	obj.myDlg = CCMyDialog:create(obj.nDialogIDD)
	obj.myDlg:setVisible(true);	
	
	local function onBtnLeftUp()
        if nil == obj.pageSGames then
        	return
        end    
		obj.pageSGames:setVisible(false)	
    end		
	obj.btnLeft = CCtrlButtonEx:create(1001, obj.myDlg)	
	obj.btnLeft:addHandleOfControlEvent(onBtnLeftUp,CCControlEventTouchUpInside)
	
	local function onBtnRightUp()	    
        if nil == obj.pageSGames then
        	return
        end
		obj.pageSGames:setVisible(true)        
    end
	
	obj.btnRight = CCtrlButtonEx:create(1002, obj.myDlg)	
	obj.btnRight:addHandleOfControlEvent(onBtnRightUp,CCControlEventTouchUpInside)	

	obj.pageSGames = CCtrlPage:create(1003, obj.myDlg)
	local page1 = DlgSmallGamePage:create()
	obj.pageSGames:AddPageItem(page1.myDlg, true)
	obj.pageSGames:setVisible(true)
	page1.myDlg:setVisible(true)
	page1.pageNum = 0
	
	--local page2 = DlgSmallGamePage:create()
	--obj.pageSGames:AddPageItem(page2.myDlg, true)
	--page2.pageNum = 1
	
	obj.pageSGames:SetCurPageIndex(0, true)
	
	local function onBtnReturnUp()
		if nil == obj.myDlg then
        	return
        end
		obj.myDlg:setVisible(false) 
    end
	
	obj.btnReturn = CCtrlButtonEx:create(1004, obj.myDlg)	
	obj.btnReturn:addHandleOfControlEvent(onBtnReturnUp,CCControlEventTouchUpInside)		
	
    return obj
end


