#include "weapon.h"

Weapon::Weapon(){
	bullet_.pos = {};
	bullet_.leftTop = {};
	bullet_.leftBottom = {};
	bullet_.rightBottom = {};
	bullet_.rightTop = {};
	bullet_.imagePos = {};
	bullet_.imageWidth = 32;
	bullet_.imageHeight = 32;
	bullet_.image;
	bullet_.color = WHITE;

	sword_.pos = {};
	sword_.leftTop = {};
	sword_.leftBottom = {};
	sword_.rightBottom = {};
	sword_.rightTop = {};
	sword_.imagePos = {};
	sword_.imageWidth = 32;
	sword_.imageHeight = 32;
	sword_.image;
	sword_.color = WHITE;

	wheelScroll_ = -60;

}
