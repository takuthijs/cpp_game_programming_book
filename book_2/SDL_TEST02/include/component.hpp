#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "actor.hpp"

class Component
{
public:
     //コンストラクター
     //updateOrderが小さいコンポーネントほど早く更新される
     Component(class Actor* owner,int updateOrder = 100);
     //デストラクター
     virtual ~Component();
     //このコンポーネントをデルタタイムで更新する
     virtual void Update(float deltaTime);
     int GetUpdateOrder()const {return mUpdateOrder;};

protected:
     //所有アクター
     class Actor* mOwner;
     //コンポーネントの更新順序
     int mUpdateOrder;
};

#endif /* COMPONENT_HPP */