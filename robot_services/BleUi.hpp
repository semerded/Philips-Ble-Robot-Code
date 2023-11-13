#ifndef BLE_UI_HPP
#define BLE_UI_HPP

#include "hal/interfaces/Gpio.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/PolymorphicVariant.hpp"
#include "services/ble/Gap.hpp"

class BleUi
    : public services::GapPeripheralObserver
{
public:
    BleUi(services::GapPeripheral& subject, hal::GpioPin& ledStandby, hal::GpioPin& ledBleInteraction);
    ~BleUi();
    void StateChanged(services::GapState state) override;

private:
    class State
    {
    public:
        explicit State(BleUi& bleUi);
        State(const State&) = delete;
        State& operator=(const State&) = delete;
        virtual ~State() = default;

        virtual void Execute() = 0;

    protected:
        BleUi& bleUi;
    };

    class StateStandby
        : public State
    {
    public:
        using State::State;

        void Execute() override;
    };

    class StateAdvertising
        : public State
    {
    public:
        using State::State;

        void Execute() override;

    private:
        infra::TimerRepeating bleInteractionTimer;
    };

    class StateConnected
        : public State
    {
    public:
        using State::State;

        void Execute() override;
    };

    class StateOff
        : public State
    {
    public:
        using State::State;

        void Execute() override;
    };

protected:
    hal::GpioPin& ledStandby;
    hal::GpioPin& ledBleInteraction;

private:
    infra::PolymorphicVariant<State, StateStandby, StateAdvertising, StateConnected, StateOff> state;
};

#endif