#ifndef SCREEN_H
#define SCREEN_H

class screen{
    public:
        screen(void);
        double getXLen(void);
        double getYLen(void);
    private:
        const double xLen;
        const double yLen;
};

#endif
