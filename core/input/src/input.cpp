#include <input.h>

#include <algorithm>
#include <cstdio>


void Action::update(const bool press_or_release, void* callback_data)
{
    if(press_or_release)
    {
        m_count++;
        // well it should never become 0 after operator++() but...
        if(m_count != m_count.min) m_state = is_released() ? State::JUST_PRESSED : State::PRESSED;
    }
    else
    {
        m_count--;
        if(m_count == m_count.min) m_state = is_pressed() ? State::JUST_RELEASED : State::RELEASED;
    }

    if(callback)
    {
        switch(callback_mode)
        {
            case CallbackMode::PRESS:
                if(is_pressed()) callback(callback_data, m_state);
                break;
            case CallbackMode::RELEASE:
                if(is_released()) callback(callback_data, m_state);
                break;
            case CallbackMode::JUST_PRESS:
                if(is_just_pressed()) callback(callback_data, m_state);
                break;
            case CallbackMode::JUST_RELEASE:
                if(is_just_released()) callback(callback_data, m_state);
                break;
            case CallbackMode::JUST_BOTH:
                if(is_just_pressed() || is_just_released()) callback(callback_data, m_state);
                break;

            case CallbackMode::BOTH:
                callback(callback_data, m_state);
            case CallbackMode::NEVER:
                break;
        }
    }
}


void Input::unbind_key(const Input::Key key)
{
    auto it = std::lower_bound(_binds.begin(), _binds.end(), key);
    if(it != _binds.end()) _binds.erase(it);
}

bool Action::is_pressed() const
{
    return m_state == State::PRESSED || m_state == State::JUST_PRESSED;
}
bool Action::is_released() const
{
    return m_state == State::RELEASED || m_state == State::JUST_RELEASED;
}
bool Action::is_just_pressed() const { return m_state == State::JUST_PRESSED; }
bool Action::is_just_released() const { return m_state == State::JUST_RELEASED; }

void Action::set_callback(void (*callback)(void* user_data, State state))
{
    this->callback = callback;
}
void Action::set_callback(void (*callback)(void* user_data, State state), const CallbackMode mode)
{
    this->callback = callback;
    this->callback_mode = mode;
}
void Action::set_callback_mode(const CallbackMode mode) { this->callback_mode = mode; }

void Input::key_cb(Input::Key key, const ButtonState state, const int mods, void* user_data)
{
    auto it = std::lower_bound(_binds.begin(), _binds.end(), key);
    bool found = it != _binds.end() && it->key == key;
    if(!found) return;
    actions_array[it->action].update(state, user_data);
}
Input::Input(Action* const actions_array, std::vector<_bindpair>&& binds)
    : actions_array(actions_array), _binds(std::move(binds))
{
}
Input::Input(Action* const actions_array) : actions_array(actions_array) {}
