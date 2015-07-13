//
//  MouseRect.h
//  WriteMouseTest
//
//  Created by wc on 15/3/4.
//
//

#ifndef __WriteMouseTest__MouseRect__
#define __WriteMouseTest__MouseRect__

#include "cocos2d.h"
#include "CucrbitManage.h"
#include "NetWorkLayer.h"
#include <vector>
#include "Network.h"

USING_NS_CC;

class MouseRect : public Sprite {
public:
    bool init();
    
    void addData(vector<double> &data);
    
    CREATE_FUNC(MouseRect);
    
private:
    vector< vector<double> > datas;
    Network net;
};

#endif /* defined(__WriteMouseTest__MouseRect__) */
