#include "robot_services/BleUi.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "services/ble/Gap.hpp"
#include <chrono>

BleUi::BleUi(services::GapPeripheral& subject, hal::GpioPin& ledStandby, hal::GpioPin& ledBleInteraction)
    : services::GapPeripheralObserver(subject)
    , ledStandby(ledStandby)
    , ledBleInteraction(ledBleInteraction)
    , state(infra::InPlaceType<StateStandby>(), *this)
{
    state->Execute();
}

BleUi::~BleUi()
{
    state.Emplace<StateOff>(*this);
    state->Execute();
}

void BleUi::StateChanged(services::GapState state)
{
    if (state == services::GapState::advertising)
        this->state.Emplace<StateAdvertising>(*this);
    else if (state == services::GapState::connected)
        this->state.Emplace<StateConnected>(*this);
    else if (state == services::GapState::standby)
        this->state.Emplace<StateStandby>(*this);

    this->state->Execute();
}

BleUi::State::State(BleUi& bleUi)
    : bleUi(bleUi)
{}

void BleUi::StateStandby::Execute()
{
    bleUi.ledStandby.Set(true);
    bleUi.ledBleInteraction.Set(false);
}

void BleUi::StateAdvertising::Execute()
{
    bleUi.ledStandby.Set(false);
    bleInteractionTimer.Start(std::chrono::milliseconds(100), [this]()
        {
            static bool ledState = true;
            bleUi.ledBleInteraction.Set(ledState);
            ledState = !ledState;
        });
}

void BleUi::StateConnected::Execute()
{
    bleUi.ledStandby.Set(false);
    bleUi.ledBleInteraction.Set(true);
}

void BleUi::StateOff::Execute()
{
    bleUi.ledStandby.Set(false);
    bleUi.ledBleInteraction.Set(false);
}
