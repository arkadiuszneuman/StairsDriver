using System;
using System.Collections.Generic;
using System.Text;

namespace StairsDriver.Simulator
{
    public class FadeInfo
    {
        private readonly int brightnessPercent;
        private readonly long startOnMillis;

        public FadeInfo(int brightnessPercent, long startOnMillis)
        {
            this.brightnessPercent = brightnessPercent;
            this.startOnMillis = startOnMillis;
        }

        public int GetBrightnessPercent()
        {
            return brightnessPercent;
        }
        public long GetStartOnMillis()
        {
            return startOnMillis;
        }
    }
}
