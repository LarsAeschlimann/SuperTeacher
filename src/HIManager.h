/**
 * \file HIManager.h
 * \brief Human Interface Manager
 * \author Samuel Dolt
 * \copyright Copyright (c) 2016 - SuperTeacher's developer.
 * \license The MIT License (MIT), see LICENSE file in the root directory
 */

#pragma once

#include <memory>
#include <boost/signals2.hpp>
#include <SFML/Window.hpp>


/**
 * This enum represent all human interface event suported by SuperTeacher.
 */
enum class HIEvent {
    FAST_DOWN,
    FAST_UP,
	GO_LEFT,
	GO_RIGHT,
	GO_UP,
	GO_DOWN,
	JUMP,
    THROW,
	CLOSE,
	DEFAULT,
    MOUSE_DOWN,
    KEY_UP
};

/**
 * Human Input Manager
 *
 * This class scan event reported by SFML Window and convert them
 * to SuperTeacher HIEvent.
 */
class HIManager {
public:
    HIManager(sf::Window *window): window(window){};

    /**
     * Process event in SFML Window Event buffer
     */
    void process(void);

    /**
     * Signal used for reporting HIEvent
     */
    boost::signals2::signal<void (HIEvent)> HIEvent_sig;

private:
    sf::Event event;
    sf::Window* window;
};

