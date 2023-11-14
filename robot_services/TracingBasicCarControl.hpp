#ifndef TRACING_BASIC_CAR_CONTROLL_HPP
#define TRACING_BASIC_CAR_CONTROLL_HPP

#include "robot_services/BasicCarControl.hpp"
#include "services/tracer/Tracer.hpp"

class TracingBasicCarControl
    : public BasicCarControl
{
public:
    TracingBasicCarControl(MotorShieldControllerDc& motorShield, services::Tracer& tracer);
    ~TracingBasicCarControl();

    void SpeedMotorLeft(uint8_t percentage, infra::Function<void()> onDone) override;
    void SpeedMotorRight(uint8_t percentage, infra::Function<void()> onDone) override;
    void DirectionMotorLeft(Direction direction, infra::Function<void()> onDone) override;
    void DirectionMotorRight(Direction direction, infra::Function<void()> onDone) override;
    void StopMotors(infra::Function<void()> onDone) override;

private:
    services::Tracer& tracer;
};

#endif