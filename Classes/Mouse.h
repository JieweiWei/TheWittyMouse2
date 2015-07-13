//
//  Mouse.h
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#ifndef __WittedMouse__Mouse__
#define __WittedMouse__Mouse__

#include "cocos2d.h"
#include "Snare.h"
#include "AnimationUtils.h"

USING_NS_CC;

class Mouse : public Sprite {
public:
    /**
     * Create the mouse
     */
    static Mouse* createMouse();
    virtual bool init();
    /**
     * The running action of the mouse
     */
    void run();
    /**
     * The jump action of the mouse
     */
    void jump();
    /**
     * The fall action of the mouse when the mouse is hit by the calabash
     */
    void fall(Snare* snare);

	/**
	* The dizzy action of the mouse when the mouse is hit by the calabash
	*/
	void dizzy();

	Sequence* createRunningSequence();

	/**
	* The action when mouse run with scooter
	*/
	void scooter();

	void speedUp();

	void slowDown();
    
	void resetSkateBoardFlag();

	void setSkateboardDif();
    /**
     * Return the IQ value
     */
    static int getIQ();
    
    /**
     * Set the IQ value
     */
    static void setIQ(int IQ_);
    
    /**
     * Return the life value
     */
    static int getLife();
    
    /**
     * Set the life value
     */
    static void setLife(int life_);

	void setDizzyDif();

	static float mouseWidth;

private:
	/**
	* create action
	*/
	Animate* createAction(const char* filename, float dif, float speed, int isLoop);
	

private:
	void resetIsAction();
	void resetDif();
	void resetSpeedup();
	void resetSlowDown();
	void resetJump();
	void setSpeedup();
	void setSlowDown();
	void setJump();
	void setFallDif();
	void resetFallingSnare();
	void moveMouseBehineSnare();
    
private:
    static int IQ;
    static int life;
	bool fallIn;
	bool isSpeedUp;
	bool isSlowDown;
	bool isJump;
	static float mousePositionY;
	static float mousePositionX;
	Size size;
	Snare* fallingSnare;
};

#endif /* defined(__WittedMouse__Mouse__) */
