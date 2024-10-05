#ifndef _RESIZEABLE_H
#define _RESIZEABLE_H

class Resizeable {
public:
    virtual ~Resizeable() = default;
    
    void registerSize(int* width, int* height);

    virtual void resize() = 0;
    
protected:
    int* m_width = nullptr;
    int* m_height = nullptr;
};

#endif