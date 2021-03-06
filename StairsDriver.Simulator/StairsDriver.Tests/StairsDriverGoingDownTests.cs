using FluentAssertions;
using StairsDriver.Simulator;
using System;
using Xunit;

namespace StairsDriver.Tests
{
    public class StairsDriverGoingDownTests
    {
        private StairsLedDriver sut = new StairsLedDriver();
        private MillisMock millisMock = new MillisMock();

        [Fact]
        public void Can_Illuminate_Led_When_Going_Down()
        {
            sut.Begin(millisMock, 3000, 1000, 400, 1);
            sut.GoDown();
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(200);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(2048);
            Update(400);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        [Fact]
        public void Can_Illuminate_Many_Leds_When_Going_Down()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 3);
            sut.GoDown();
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(1000);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(2000);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        [Fact]
        public void Can_Deilluminate_Many_Leds_When_Going_Down()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 3);
            sut.GoDown();
            Update(2000);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            Update(5000);
            Update(6000);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        [Fact]
        public void Can_Deilluminate_And_Then_Illuminate_Many_Leds_When_Going_Down_Two_Times()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 4);
            sut.GoDown();
            Update(5000);
            Update(6250);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(1024);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(3072);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            sut.GoDown();
            Update(6500);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(1024);
            Update(6750);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(1024);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(3072);
        }

        [Fact]
        public void Can_Deilluminate_And_Then_Illuminate_Many_Leds_When_Going_Down_Two_Times_When_Led1_Is_Not_Totally_Off()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 4);
            sut.GoDown();
            Update(5000);
            Update(5500);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            sut.GoDown();
            Update(5750);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(3072);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(3072);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(5999);
            Update(6000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(2052);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(6500);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(10500);
            Update(13000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
        }

        [Fact]
        public void Can_Illuminate_And_Deilluminate_Many_Leds_When_Going_Down_And_Lower_Sensor_Triggers_After_All_Leds_Are_On()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 3);
            sut.GoDown();
            Update(2000);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(3000);
            sut.GoUp();
            Update(8000);
            Update(8500);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(9000);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(9500);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(2048);
        }

        private void Update(int currentMillis)
        {
            millisMock.Millis = currentMillis;
            sut.Update();
        }
    }
}
