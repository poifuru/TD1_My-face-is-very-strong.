#include "weapon.h"

Weapon::Weapon(){
	bullet_.pos = {};
	bullet_.leftTop = {};
	bullet_.leftBottom = {};
	bullet_.rightBottom = {};
	bullet_.rightTop = {};
	bullet_.imagePos = {};
	bullet_.width = 32;
	bullet_.height = 32;
	bullet_.image;
	bullet_.color = WHITE;

	sword_.pos = {};
	sword_.leftTop = {};
	sword_.leftBottom = {};
	sword_.rightBottom = {};
	sword_.rightTop = {};
	sword_.imagePos = {};
	sword_.width = 32;
	sword_.height = 32;
	sword_.image;
	sword_.color = WHITE;
}
