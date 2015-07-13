//
//  HUDLayer.h
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#ifndef __WittedMouse__HUDLayer__
#define __WittedMouse__HUDLayer__

#include "cocos2d.h"

USING_NS_CC;

class HUDLayer : public Layer {
public:
    bool init();
    
    /**
     * Initialize the IQ label
     */
    void initIQLabel();
    void initRouteLabel();
    void updateIQ();
    void updateRoute();

    CREATE_FUNC(HUDLayer);
    
    ///< IQ label
    Label *IQLabel;
};

#endif /* defined(__WittedMouse__HUDLayer__) */
