#include "pzhelp"

PROGRAM { 			
    WRITELN("1. Electrical"); 
    WRITELN("2. Mechanical"); 
    WRITELN("3. Chemical"); 
    WRITELN("4. Civil"); 
    WRITELN("5. Architecture");
    WRITELN("6. Rural");
    WRITELN("7. Metallurgical");
    WRITELN("8. Naval");
    WRITELN("9. Applied Mathematical and Physical Sciences");     
    WRITELN("10. idk");

    WRITE("Insert the number corresponding your school: ");
    int x;
    x = READ_INT();
    if (x>0 AND x<11){
        switch(x){
	        case 1: WRITELN("You'll live in great pain and suffering - also you're not God"); break;
		case 2: WRITELN("robots go brrrr"); break;
		case 3: WRITELN("jesse, we need to cook"); break;
	        case 4: WRITELN("you're better than arch"); break;
	        case 5: WRITELN("you're better than civil"); break;
	        case 6: WRITELN("tractor racing simulations or smth idk"); break;
	        case 7: WRITELN("*minecraft steve oof*"); break;
	        case 8: WRITELN("*titanic theme in a high-pitched demonic flute*"); break;
	        case 9: WRITELN("you're not an engineer, go to uoa"); break;
		case 10: WRITELN("its okay, not everyone is qualified enough to study somewhere"); break;
        }
    }
        else WRITELN("That's cheating!");
}
