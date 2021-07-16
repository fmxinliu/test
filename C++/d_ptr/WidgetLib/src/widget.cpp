#include "widget.h"


////////////////////////
// v2.x、v3.x 数据封装
////////////////////////
#if V2_0 || V2_1 || V3_X
class WidgetPrivate
{
    friend Widget;
public:
    // v3.x新增 q 指针，可访问外部 API 类
#if V3_X
    WidgetPrivate(Widget *q) : q_ptr(q) {}
    void Func() { q_ptr->update(); }
#endif

private:
    Rect m_geometry;

    // 相比于v2.0版本，v2.1、v3.x新增成员
#if V2_1 || V3_X
    std::string m_stylesheet;
#endif

#if V3_X
    Widget *q_ptr; // q 指针
#endif
};

#endif


Widget::Widget()
    // v1.x 数据未封装
#if V1_1
    : m_stylesheet("stylesheet")
    // v2.x数据已封装
#elif V2_0 || V2_1
    : d_ptr(new WidgetPrivate)
    // v3.x数据已封装，且添加 q 指针
#elif V3_X
    : d_ptr(new WidgetPrivate(this))
#endif
{
}

Widget::~Widget()
{
    // v2.x、v3.x 释放 d 指针
#if V2_0 || V2_1 || V3_X
    delete d_ptr;
    d_ptr = NULL;
#endif
}

Rect Widget::geometry() const
{
     // v1.x 直接访问
#if V1_0 || V1_1
    return m_geometry;
     // v2.x、v3.x 通过 d 指针访问
#elif V2_0 || V2_1 || V3_X
    return d_ptr->m_geometry;
#endif
}

////////////////////////
// v1.1、v2.1、v3.x新增
////////////////////////
#if V1_1 || V2_1 || V3_X
string Widget::stylesheet() const
{
#if V1_1
    return m_stylesheet; 
#else
    return d_ptr->m_stylesheet;
#endif
}
#endif 


string Widget::version()
{
#if V1_0
    return "v1.0";
#elif V1_1
    return "v1.1";
#elif V2_0
    return "v2.0";
#elif V2_1
    return "v2.1";
#elif V3_X
    return "v3.x";
#endif
}

#if V3_X
void Widget::update()
{
    printf("Widget::update()\r\n");
}

void Widget::repaint()
{
    printf("Widget::repaint()\r\n");
}
#endif