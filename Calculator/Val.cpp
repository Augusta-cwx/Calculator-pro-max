#include"Val.h"
Const Con;
Val::Val(char c) {
	switch (t = c) {
	case 'E':case 'P':case 'x':case 'y':case 'z':case 'a':case 'b':case 'c': {
		v = Con[t];
		break;
	}
	case '#': {
		v = rand_double();
		break;
	}
	}
}