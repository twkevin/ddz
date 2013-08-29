
package.path = package.path .. ';./lua/protobuf/?.lua'
require("person_pb")
require("item_pb")

function testloadplayer()
    
  
    local msg = item_pb.load_item()    
    
    local item1 = msg.items:add()
    item1.id = 1234
    item1.type = 2 
    item1.amount = 5
    
    local item2 = msg.items:add()
    item2.id = 1234
    item2.type = 2 
    item2.amount = 5 
    
    local data = msg:SerializeToString()
    
    local msg2 = item_pb.load_item()
	msg2:ParseFromString(data)
	
	local msgNew = item_pb.load_item()
	msgNew:ParseFromString(data)	
    local tmpItems = msgNew.items
    local sizeItems = #tmpItems
    local tmpItem1 = tmpItems[1]
    local tmpItem1ID = tmpItem1.id

    
    local pb=require("test_pb")
    local test=pb.test()
    test.v:append(1)
    test.v:append(2)
    test.x:append("test1")
    test.x:append("test2")
    
    local str=test:SerializeToString()
    
    local new=pb.test()
    new:ParseFromString(str)
    
    local xx = new.v
    local x1 = xx[1]    
    local x2 = new.v[2]
    local size = #xx




    return 1
end

function testProtoc()
    local msg = person_pb.Person()
	msg.name = "John Doe"
	msg.id = 1234
	msg.email = "jdoe@example.com"

	local home = msg.Extensions[person_pb.Phone.phones]:add()
	home.num = "2147483647"
	home.type = person_pb.Phone.HOME

	--pb.print(msg)
	local data = msg:SerializeToString()
	--print("bytes =", #bin)

	--print("Decode person message from binary.")
	local msg2 = person_pb.Person()
	msg2:ParseFromString(data)
	--pb.print(msg2)
	local msgid = msg2.id
	
	return msgid
end