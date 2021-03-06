//
// Created by Thong Tran on 2021-09-25.
//

#ifndef COMP345_N11_ORDERS_H
#define COMP345_N11_ORDERS_H


//#pragma once

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Logging/LoggingObserver.h"
#include <iostream>
#include <vector>
using namespace std;
class Player;
class Territory;
class Order;


enum OrderType : short
{
    DEPLOY,
    ADVANCE,
    BOMB,
    BLOCKADE,
    AIRLIFT,
    NEGOTIATE,
};

string toString (short enumType);

class Order : public Subject
{
public:
    /**
     *
     */
    virtual ~Order();
    friend std::ostream &operator<<(std::ostream &output, const Order &order);\
//    ???

    void execute();
    int getPriority() const;
    virtual Order* clone() const = 0;
    virtual bool validate() const = 0;
    virtual OrderType getType() const = 0;

    // Iloggable
    virtual string stringToLog();

protected:
    Player* issuer_;
    Order();
    Order(Player* issuer, int priority);
    Order(const Order &order);

    const Order &operator=(const Order &order);
    virtual std::ostream &print_(std::ostream &output) const = 0;
    virtual void execute_() = 0;
    virtual void undo_();

private:
    int priority_;
};

/***
 * The OrderList class contains...
 */
class OrdersList : public Subject
{
public:

    OrdersList();
    OrdersList(const OrdersList &orders);
    OrdersList(vector<Order *> orders);
    ~OrdersList();
    const OrdersList &operator=(const OrdersList &orders);
    friend std::ostream &operator<<(std::ostream &output, const OrdersList &orders);
    std::vector<Order*> getOrders() const;
    void setOrders(std::vector<Order*> orders);
    Order* popTopOrder();
    Order* peek();
    int size() const;
    void add(Order* order);
    void move(int area, int targetRange);
    void remove(int target);
    void removeOrder(Order * order);

    // Iloggable
    virtual string stringToLog();
private:
    std::vector<Order*> orders_;
};

/**
 * DeployOrder class contains
 */

class DeployOrder : public Order
{
public:
    DeployOrder();
    DeployOrder(Player* issuer, int numberOfArmies, Territory* destination);
    DeployOrder(const DeployOrder &order);
    const DeployOrder &operator=(const DeployOrder &order);
    Order* clone() const;
    void addArmies(int additional);
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* destination_;
};


/**
 * AirLiftOrder contains
 */

class AirliftOrder : public Order
{
public:
    AirliftOrder();
    AirliftOrder(Player* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AirliftOrder(const AirliftOrder &order);
    const AirliftOrder &operator=(const AirliftOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* source_;
    Territory* destination_;
};


class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    NegotiateOrder(Player* issuer, Player* target);
    NegotiateOrder(const NegotiateOrder &order);
    const NegotiateOrder &operator=(const NegotiateOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Player* target_;
};

/**
 * AdvanceOrder class contains
 */

class AdvanceOrder : public Order
{
public:
    AdvanceOrder();
    AdvanceOrder(Player* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AdvanceOrder(const AdvanceOrder &order);
    const AdvanceOrder &operator=(const AdvanceOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* source_;
    Territory* destination_;
};

/**
 * BomOrder class contains
 */

class BombOrder : public Order
{
public:
    BombOrder();
    BombOrder(Player* issuer, Territory* target);
    BombOrder(const BombOrder &order);
    const BombOrder &operator=(const BombOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* target_;
};

/**
 * BlockadeOrder class contains
 */

class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    BlockadeOrder(Player* issuer, Territory* territory);
    BlockadeOrder(const BlockadeOrder &order);
    const BlockadeOrder &operator=(const BlockadeOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

    // Iloggable
    virtual string stringToLog();
protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* territory_;
};

#endif //COMP345_N11_MAP_H