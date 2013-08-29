#include "common_macro_define.h"
#define QX_COMBINE(a, b)         QX_COMBINE1(a, b)
#define QX_COMBINE1(a, b)        a##b

#define QX_I_DELEGATE        QX_COMBINE(IDelegate, QX_SUFFIX)

#define QX_C_STATIC_DELEGATE         QX_COMBINE(CStaticDelegate, QX_SUFFIX)
#define QX_C_METHOD_DELEGATE         QX_COMBINE(CMethodDelegate, QX_SUFFIX)

#define QX_C_DELEGATE        QX_COMBINE(CDelegate, QX_SUFFIX)
#define QX_C_MULTI_DELEGATE      QX_COMBINE(CMultiDelegate, QX_SUFFIX)

    // 委托基类
    QX_TEMPLATE QX_TEMPLATE_PARAMS
    class QX_DLL_FORCE_EXPORT QX_I_DELEGATE
    {
    public:
        virtual ~QX_I_DELEGATE() { }
        virtual bool isType(const std::type_info& _type) = 0;
        virtual void invoke(QX_PARAMS) = 0;
        virtual bool compare(QX_I_DELEGATE QX_TEMPLATE_ARGS* _delegate) const = 0;
    };

    // 静态方法委托类
    QX_TEMPLATE QX_TEMPLATE_PARAMS
    class QX_DLL_FORCE_EXPORT QX_C_STATIC_DELEGATE
        : public QX_I_DELEGATE QX_TEMPLATE_ARGS
    {
    public:
        typedef void (*Func)(QX_PARAMS);

        QX_C_STATIC_DELEGATE (Func _func) : mFunc(_func) { }

        virtual bool isType(const std::type_info& _type) { return typeid(QX_C_STATIC_DELEGATE QX_TEMPLATE_ARGS) == _type; }

        virtual void invoke(QX_PARAMS)
        {
            mFunc(QX_ARGS);
        }

        virtual bool compare(QX_I_DELEGATE QX_TEMPLATE_ARGS* _delegate) const
        {
            if (0 == _delegate || !_delegate->isType(typeid(QX_C_STATIC_DELEGATE QX_TEMPLATE_ARGS))) return false;
            QX_C_STATIC_DELEGATE QX_TEMPLATE_ARGS* cast = static_cast<QX_C_STATIC_DELEGATE QX_TEMPLATE_ARGS*>(_delegate);
            return cast->mFunc == mFunc;
        }

    private:
        Func mFunc;
    };

    // 类方法委托类
    template QX_T_TEMPLATE_PARAMS
    class QX_DLL_FORCE_EXPORT QX_C_METHOD_DELEGATE
        : public QX_I_DELEGATE QX_TEMPLATE_ARGS
    {
    public:
        typedef void(T::*Method)(QX_PARAMS);

        QX_C_METHOD_DELEGATE(T * _object, Method _method): mObject(_object), mMethod(_method) { }

        virtual bool isType(const std::type_info& _type) { return typeid(QX_C_METHOD_DELEGATE QX_T_TEMPLATE_ARGS) == _type; }

        virtual void invoke(QX_PARAMS)
        {
            (mObject->*mMethod)(QX_ARGS);
        }

        virtual bool compare(QX_I_DELEGATE QX_TEMPLATE_ARGS* _delegate) const
        {
            if (0 == _delegate || !_delegate->isType(typeid(QX_C_METHOD_DELEGATE QX_T_TEMPLATE_ARGS))) return false;
            QX_C_METHOD_DELEGATE QX_T_TEMPLATE_ARGS  * cast = static_cast<  QX_C_METHOD_DELEGATE QX_T_TEMPLATE_ARGS  * >(_delegate);
            return cast->mObject == mObject && cast->mMethod == mMethod;
        }

    private:
        T * mObject;
        Method mMethod;
    };


// newDelegate beg
// new静态方法委托
// newDelegate(class_name::static_method_name);
QX_TEMPLATE   QX_TEMPLATE_PARAMS
inline QX_DLL_FORCE_EXPORT QX_I_DELEGATE QX_TEMPLATE_ARGS  * newDelegate(void (*_func)(QX_PARAMS))
{
    return new QX_C_STATIC_DELEGATE QX_TEMPLATE_ARGS  (_func);
}

// new类方法委托
// newDelegate(&object_name, &class_name::method_name);
template QX_T_TEMPLATE_PARAMS
inline QX_DLL_FORCE_EXPORT QX_I_DELEGATE QX_TEMPLATE_ARGS  * newDelegate(T * _object, void (T::*_method)(QX_PARAMS))
{
    return new QX_C_METHOD_DELEGATE  QX_T_TEMPLATE_ARGS  (_object, _method);
}
// newDelegate end

    // 单委托
    QX_TEMPLATE   QX_TEMPLATE_PARAMS
    class QX_DLL_FORCE_EXPORT QX_C_DELEGATE
    {
    public:
        typedef  QX_I_DELEGATE QX_TEMPLATE_ARGS  IDelegate;

        QX_C_DELEGATE () : mDelegate(0) { }
        QX_C_DELEGATE (const QX_C_DELEGATE  QX_TEMPLATE_ARGS& _event)
        {
            mDelegate = _event.mDelegate;
            const_cast<QX_C_DELEGATE  QX_TEMPLATE_ARGS&>(_event).mDelegate = 0;
        }
        ~QX_C_DELEGATE () { clear(); }

        bool empty() const { return mDelegate == 0; }

        void clear()
        {
            if (mDelegate)
            {
                delete mDelegate;
                mDelegate = 0;
            }
        }

        QX_C_DELEGATE  QX_TEMPLATE_ARGS& operator=(IDelegate* _delegate)
        {
            delete mDelegate;
            mDelegate = _delegate;
            return *this;
        }

        QX_C_DELEGATE  QX_TEMPLATE_ARGS& operator=(const QX_C_DELEGATE  QX_TEMPLATE_ARGS& _event)
        {
            delete mDelegate;
            mDelegate = _event.mDelegate;
            const_cast<QX_C_DELEGATE  QX_TEMPLATE_ARGS&>(_event).mDelegate = 0;

            return *this;
        }

        void operator()(QX_PARAMS)
        {
            if (mDelegate == 0) return;
            mDelegate->invoke(QX_ARGS);
        }

    private:
        IDelegate * mDelegate;
    };

    // 多委托
    QX_TEMPLATE   QX_TEMPLATE_PARAMS
    class QX_DLL_FORCE_EXPORT QX_C_MULTI_DELEGATE
    {
    public:
        typedef QX_I_DELEGATE QX_TEMPLATE_ARGS    IDelegate;
        typedef QX_TYPENAME std::list<IDelegate*>    ListDelegate;
        typedef QX_TYPENAME ListDelegate::iterator   ListDelegateIterator;
        typedef QX_TYPENAME ListDelegate::const_iterator ConstListDelegateIterator;

        QX_C_MULTI_DELEGATE () { }
        ~QX_C_MULTI_DELEGATE () { clear(); }

        bool empty() const
        {
            for (ConstListDelegateIterator iter = mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if (*iter) return false;
            }
            return true;
        }

        void clear()
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if (*iter)
                {
                    delete (*iter);
                    (*iter) = 0;
                }
            }
        }

        QX_C_MULTI_DELEGATE  QX_TEMPLATE_ARGS & operator+=(IDelegate* _delegate)
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if ((*iter) && (*iter)->compare(_delegate))
                {
                    assert(false);//, "dublicate delegate");
                }
            }
            mListDelegates.push_back(_delegate);
            return *this;
        }

        QX_C_MULTI_DELEGATE  QX_TEMPLATE_ARGS & operator-=(IDelegate* _delegate)
        {
            for (ListDelegateIterator iter=mListDelegates.begin(); iter!=mListDelegates.end(); ++iter)
            {
                if ((*iter) && (*iter)->compare(_delegate))
                {
                    if ((*iter) != _delegate) delete (*iter);
                    (*iter) = 0;
                    break;
                }
            }
            delete _delegate;
            return *this;
        }

        void operator()(QX_PARAMS)
        {
            ListDelegateIterator iter = mListDelegates.begin();
            while (iter != mListDelegates.end())
            {
                if (0 == (*iter))
                {
                    iter = mListDelegates.erase(iter);
                }
                else
                {
                    (*iter)->invoke(QX_ARGS);
                    ++iter;
                }
            }
        }

    private:
        // constructor and operator =, without implementation, just for private
        QX_C_MULTI_DELEGATE (const QX_C_MULTI_DELEGATE  QX_TEMPLATE_ARGS & _event);
        QX_C_MULTI_DELEGATE  QX_TEMPLATE_ARGS & operator=(const QX_C_MULTI_DELEGATE  QX_TEMPLATE_ARGS & _event);


    private:
        ListDelegate mListDelegates;

    };

// 撤销定义的字符串
#undef QX_COMBINE
#undef QX_COMBINE1

#undef QX_I_DELEGATE

#undef QX_C_STATIC_DELEGATE
#undef QX_C_METHOD_DELEGATE

#undef QX_C_DELEGATE
#undef QX_C_MULTI_DELEGATE

#undef QX_SUFFIX
#undef QX_TEMPLATE
#undef QX_TEMPLATE_PARAMS
#undef QX_TEMPLATE_ARGS
#undef QX_T_TEMPLATE_PARAMS
#undef QX_T_TEMPLATE_ARGS
#undef QX_PARAMS
#undef QX_ARGS
#undef QX_TYPENAME

