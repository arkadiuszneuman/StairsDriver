using FluentAssertions;
using StairsDriver.Simulator;
using Xunit;

namespace StairsDriver.Tests
{
    public class StairsDriverGoingUpAndDownTests
    {
        private StairsLedDriver sut = new StairsLedDriver();
        private MillisMock millisMock = new MillisMock();

        [Fact]
        public void Can_Illuminate_Many_Leds_When_Going_Up_And_Down_At_Same_Time_And_Down_Is_First()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 4);
            sut.GoDown();
            sut.GoUp();
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(1000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(2000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        [Fact]
        public void Can_Illuminate_Many_Leds_When_Going_Up_And_Down_At_Same_Time_And_Up_Is_First()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 4);
            sut.GoUp();
            sut.GoDown();
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(1000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(2000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        [Fact]
        public void Can_Illuminate_Many_Leds_When_Going_Up_And_Down_At_Same_Different()
        {
            sut.Begin(millisMock, 5000, 500, 1000, 4);
            sut.GoDown();
            sut.GoUp();
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(0);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(0);
            Update(1000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(2048);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
            Update(2000);
            sut.ledStrips[3].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[2].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[1].GetCurrentBrightness().Should().Be(4096);
            sut.ledStrips[0].GetCurrentBrightness().Should().Be(4096);
        }

        private void Update(int currentMillis)
        {
            millisMock.Millis = currentMillis;
            sut.Update();
        }
    }
}
