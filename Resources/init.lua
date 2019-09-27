VisualMode('VISIBLE')
hero=Character(1)
hero:Place(20,1)
print(hero)
baddie=Character(2)
print(baddie)
bars=Doodad(8)

fence=Doodad(7)




function baddiedead()
   if baddie:GetState() == 4
   then return true
   else return false
   end   
end

function barsopen()
   if bars:GetState() == 0
   then return true
   else return false
   end
   
end


function cattlefree()
   if fence:GetState() == 0
   then return true
   else return false
   end
end


function alwaystrue()
   return true
end




print(alwaystrue())

print("Done Initializing Lua")
