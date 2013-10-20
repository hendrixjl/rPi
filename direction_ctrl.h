#ifndef __DIRECTION_CTRL_H__
#define __DIRECTION_CTRL_H__

/**
 * This abstract class conceptualizes direction which may be either forward,stop,backwards or
 * right, stop left or even up,stop,down.
 */
 
class direction_ctrl
{
public:
    ~direction_ctrl() {}
    virtual void go()=0; // one way
    virtual void stop()=0; // stop
    virtual void back()=0; // the other way
};

#endif
