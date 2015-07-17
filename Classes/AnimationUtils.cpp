#include "AnimationUtils.h"

Animation* AnimationUtils::createWithName(const char* name, float delay, int loops) {
	return createWithNameAndStartIndex(name, 0, delay, loops);
}

Animation* AnimationUtils::createWithNameAndStartIndex(const char* name, int startIndex, float delay, int loops) {
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	int index = startIndex;
	do {
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%02d.png", name, index++));
		if (frame == NULL) {
			break;
		}
		frameVec.pushBack(frame);
	} while (true);
	Animation* animation = Animation::createWithSpriteFrames(frameVec, delay, loops);
	animation->setRestoreOriginalFrame(true);
	return animation;
}

Animation* AnimationUtils::createWithNameAndNum(const char* name, int num, float delay, int loops) {
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	for (int i = 0; i < num; ++i) {
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%02d.png", name, i));
		if (frame == NULL) {
			break;
		}
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, delay, loops);
	animation->setRestoreOriginalFrame(true);
	return animation;
}
