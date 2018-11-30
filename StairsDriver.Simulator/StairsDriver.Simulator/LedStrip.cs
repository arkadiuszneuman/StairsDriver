using System;

namespace StairsDriver.Simulator
{
    public class LedStrip
    {
        MillisMock millisMock;
        int milisCountForFullBrightness;
        bool isFadingPlanned;
        bool brightnessGoingUp;
        long millisStart;
        int minLevel = 0;
        int maxLevel = 100;
        int brightnessToSet;
        int MAX_LED_BRIGHTNESS = 4096;
        int currentBrightness;
        double previousTimeLeftPercent;
        bool isFading;
        FadeInfo fadePlan;

        public LedStrip(MillisMock millisMock, int milisCountForFullBrightness)
        {
            this.milisCountForFullBrightness = milisCountForFullBrightness;
            this.millisMock = millisMock;
        }

        long millis()
        {
            return millisMock.Millis;
        }

        public void Fade(int brightnessPercent, int delay)
        {
            long currentMillisStart = millis() + delay;

            //if (this.isFadingPlanned && !this.brightnessGoingUp)
            //{
            //    if (this.millisStart < currentMillisStart)
            //        return;
            //}

            if (brightnessPercent > this.maxLevel)
                brightnessPercent = this.maxLevel;
            if (brightnessPercent < this.minLevel)
                brightnessPercent = this.minLevel;

            this.brightnessToSet = (int)(brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100);

            this.brightnessGoingUp = this.brightnessToSet > this.currentBrightness;
            this.millisStart = currentMillisStart;
            this.isFadingPlanned = true;
            this.previousTimeLeftPercent = 0;
        }

        public void AddFadePlan(int brightnessPercent, int delay)
        {
            //if (this.fadePlan)
            //	delete this.fadePlan;
            this.fadePlan = new FadeInfo(brightnessPercent, millis() + delay);
            Update();
        }

        public void Update()
        {
            if (fadePlan != null)
            {
                int delay = (int)(fadePlan.GetStartOnMillis() - millis());
                if (delay <= 0)
                {
                    Fade(this.fadePlan.GetBrightnessPercent(), delay);
                    //delete this.fadePlan;
                    fadePlan = null;
                }
            }

            if (!this.isFadingPlanned)
                return;

            long currentMillis = millis();
            if (currentMillis >= millisStart)
            {
                this.isFading = true;
                long difference = currentMillis - millisStart;

                double timeLeftPercent = difference * 1.0 * 100 / this.milisCountForFullBrightness;

                if (timeLeftPercent - this.previousTimeLeftPercent > 0)
                {
                    if (this.brightnessGoingUp)
                        this.currentBrightness += (int)Math.Round((timeLeftPercent - this.previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100, 0);
                    else
                        this.currentBrightness -= (int)Math.Round((timeLeftPercent - this.previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100, 0);

                    this.previousTimeLeftPercent = timeLeftPercent;

                    if (timeLeftPercent >= 100 ||
                        (brightnessGoingUp && currentBrightness >= brightnessToSet) ||
                        (!brightnessGoingUp && currentBrightness <= brightnessToSet))
                    {
                        this.currentBrightness = this.brightnessToSet;
                        this.isFadingPlanned = this.isFading = false;
                        this.millisStart = 0;
                    }

                    SetPWM(this.currentBrightness);
                }
            }
        }

        private void SetPWM(int pwmValue)
        {
            if (pwmValue >= MAX_LED_BRIGHTNESS)
                pwmValue = MAX_LED_BRIGHTNESS;
            else if (pwmValue <= 0)
                pwmValue = 0;
            else
                pwmValue = MAX_LED_BRIGHTNESS - pwmValue;
        }

        public bool IsBrightnessGoingUp()
        {
            return this.brightnessGoingUp;
        }

        public bool IsFading()
        {
            return this.isFading;
        }

        public bool IsFadePlanned()
        {
            return this.isFadingPlanned;
        }

        public FadeInfo GetFadePlan()
        {
            return this.fadePlan;
        }

        public double GetCurrentBrightness()
        {
            return this.currentBrightness;
        }

        public void SetMinLevel(int minLevel)
        {
            this.minLevel = minLevel;
            Fade(this.minLevel, 0);
        }

        public void SetMaxLevel(int maxLevel)
        {
            this.maxLevel = maxLevel;
        }

        public int GetMinLevelPwm()
        {
            return (int)(this.minLevel * 1.0 * MAX_LED_BRIGHTNESS / 100);
        }

        public int GetMaxLevelPwm()
        {
            return (int)(this.maxLevel * 1.0 * MAX_LED_BRIGHTNESS / 100);
        }

        public bool IsFadedToMinLevel()
        {
            return GetCurrentBrightness() == GetMinLevelPwm();
        }

        public bool IsFadedToMaxLevel()
        {
            return GetCurrentBrightness() == GetMaxLevelPwm();
        }
    }
}
