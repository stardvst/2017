#ifndef MVC_H
#define MVC_H

#include <string>
#include <list>
#include <set>

/// Abstract base class Observer
/**
    Common ancestor for view and controller
*/
class Observer {
public:
    virtual void update() {} // default is no-op
};

/// Model class
/**
    The class that holds data, and some functionality
*/
class Model {
public:
    Model(const std::string &party);

    // access interface for modification by controller
    void clear_votes(); // set voting values to 0
    void change_vote(const std::string &party, long vote);

    // factory functions for view access to data
    std::list<std::string>::const_iterator get_party_iter() const { return m_parties.begin(); }
    std::list<long>::const_iterator get_vote_iter() const { return m_votes.begin(); }

    // methods to allow observing objects to subscribe and unsubscribe
    void attach(Observer *const observer) { m_registry.insert(observer); }
    void detach(Observer *const observer) { m_registry.erase(observer); }

protected:
    virtual void notify(); // is called by ALL methods that modify the model

private:
    std::list<std::string> m_parties;
    std::list<long> m_votes;

    std::set<Observer *> m_registry;
};

/// Base class View
/**
    The base class for all View classes
*/
class View : public Observer {
public: 
    View(Model *const model)
        : m_model(model)
        , m_controller(nullptr) {
        m_model->attach(this); // subscribe to change-propagation mechanism
    }

    virtual ~View() { m_model->detach(this); } // unsubscribe from change-propagation mechanism

    virtual void initialize();
    virtual void draw(); // (re-)display view
    
    virtual void update() { // redefining abstract interface
        draw(); // acquires data to be displayed from the model
    }

    Model *get_model() const { return m_model; }
    Controller *get_controller() const { return m_controller; }

protected:
    Model *m_model;
    Controller *m_controller;
};

/// BarChartView class
/**
    A concrete View class
*/
class BarChartView : public View {
public:
    BarChartView(Model *const model) : View(model) {}
    
    virtual void draw() {
        std::list<std::string>::const_iterator it_party = m_model->get_party_iter();
        std::list<long>::const_iterator it_vote = m_model->get_vote_iter();

        std::list<long> list; // for scaling values to fill the screen
        long max = 1; // maximum for adjustment


    }
};

class Controller : public Observer {
public:
private:
};

#endif // !MVC_H