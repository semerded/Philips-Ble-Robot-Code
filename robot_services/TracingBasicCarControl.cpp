#include "robot_services/TracingBasicCarControl.hpp"
#include "infra/util/EnumCast.hpp"


TracingBasicCarControl::TracingBasicCarControl(MotorShieldControllerDc& motorShield, services::Tracer& tracer)
    : BasicCarControl(motorShield)
    , tracer(tracer)
{}

TracingBasicCarControl::~TracingBasicCarControl()
{}

void TracingBasicCarControl::SpeedMotorLeft(uint8_t percentage, infra::Function<void()> onDone)
{
    tracer.Trace() << "TracingBasicCarControl::SpeedMotorLeft " << percentage;
    BasicCarControl::SpeedMotorLeft(percentage, onDone);
}

void TracingBasicCarControl::SpeedMotorRight(uint8_t percentage, infra::Function<void()> onDone)
{
    tracer.Trace() << "TracingBasicCarControl::SpeedMotorRight " << percentage;
    BasicCarControl::SpeedMotorRight(percentage, onDone);
}

void TracingBasicCarControl::DirectionMotorLeft(Direction direction, infra::Function<void()> onDone)
{
    tracer.Trace() << "TracingBasicCarControl::DirectionMotorLeft " << infra::enum_cast(direction);
    BasicCarControl::DirectionMotorLeft(direction, onDone);
}

void TracingBasicCarControl::DirectionMotorRight(Direction direction, infra::Function<void()> onDone)
{
    tracer.Trace() << "TracingBasicCarControl::DirectionMotorRight " << infra::enum_cast(direction);
    BasicCarControl::DirectionMotorRight(direction, onDone);
}

void TracingBasicCarControl::StopMotors(infra::Function<void()> onDone)
{
    tracer.Trace() << "TracingBasicCarControl::StopMotors";
    BasicCarControl::StopMotors(onDone);
}