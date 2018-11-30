namespace StairsDriver.Simulator
{
    public class StairsLedDriver
    {
        int timeForLedsSwitchedOn;
        int delayForNextStairToSwitchOn;
        int millisCountForFullBrightness;
        int stairsCount;
        public LedStrip[] ledStrips;
        private MillisMock millisMock;
        int state;
        int STAIRS_OFF = 0, STAIRS_GO_UP = 1, STAIRS_GO_DOWN = 2, STAIRS_GO_UP_AND_DOWN = 3;
        long timeOfLastSensorDetected;

        public void Begin(MillisMock millisMock, int timeForLedsSwitchedOn, int delayForNextStairToSwitchOn, int millisCountForFullBrightness,
            int stairsCount)
        {
            this.millisMock = millisMock;
            this.timeForLedsSwitchedOn = timeForLedsSwitchedOn;
            this.delayForNextStairToSwitchOn = delayForNextStairToSwitchOn;
            this.millisCountForFullBrightness = millisCountForFullBrightness;
            this.stairsCount = stairsCount;

            this.ledStrips = new LedStrip[this.stairsCount];
            for (int i = 0; i < this.stairsCount; i++)
                this.ledStrips[i] = new LedStrip(millisMock, this.millisCountForFullBrightness);

        }

        private long millis()
        {
            return this.millisMock.Millis;
        }

        public void GoUp()
        {
            if ((this.state == STAIRS_GO_DOWN || this.state == STAIRS_OFF || ledStrips[0].IsFadedToMinLevel() || !ledStrips[0].IsBrightnessGoingUp())
                )
            {
                bool isAnyFaded = false;

                for (int i = 0; i < stairsCount; ++i)
                {
                    if (!ledStrips[i].IsBrightnessGoingUp())
                    {
                        int delay = i * this.delayForNextStairToSwitchOn;
                        FadeInfo fadePlan = ledStrips[i].GetFadePlan();
                        if (fadePlan == null || fadePlan.GetStartOnMillis() > delay + millis())
                        {
                            ledStrips[i].AddFadePlan(100, delay);
                            isAnyFaded = true;
                        }

                    }
                }

                if (isAnyFaded)
                {
                    if (this.state == STAIRS_GO_DOWN)
                        this.state = STAIRS_GO_UP_AND_DOWN;
                    else
                        this.state = STAIRS_GO_UP;
                }
            }

            this.timeOfLastSensorDetected = millis();
        }

        public void GoDown()
        {
            if ((this.state == STAIRS_GO_UP || this.state == STAIRS_OFF || ledStrips[stairsCount - 1].IsFadedToMinLevel() || !ledStrips[stairsCount - 1].IsBrightnessGoingUp())
                )
            {
                bool isAnyFaded = false;

                for (int i = 0; i < stairsCount; ++i)
                {
                    int currentLedStrip = stairsCount - i - 1;

                    if (!ledStrips[currentLedStrip].IsBrightnessGoingUp())
                    {
                        int delay = i * this.delayForNextStairToSwitchOn;
                        FadeInfo fadePlan = ledStrips[currentLedStrip].GetFadePlan();
                        if (fadePlan == null || fadePlan.GetStartOnMillis() > delay + millis())
                        {
                            ledStrips[currentLedStrip].AddFadePlan(100, delay);
                            isAnyFaded = true;
                        }
                    }
                }

                if (isAnyFaded)
                {
                    if (this.state == STAIRS_GO_UP)
                        this.state = STAIRS_GO_UP_AND_DOWN;
                    else
                        this.state = STAIRS_GO_DOWN;
                }
            }

            this.timeOfLastSensorDetected = millis();
        }

        public void Update()
        {
            for (int i = 0; i < this.stairsCount; ++i)
            {
                ledStrips[i].Update();
            }

            if (state > STAIRS_OFF)
            {
                if (millis() - this.timeOfLastSensorDetected >= this.timeForLedsSwitchedOn)
                {
                    bool allStairsAreOff = true;

                    if (state == STAIRS_GO_UP)
                    {
                        for (int i = 0; i < stairsCount; ++i)
                        {
                            if (ledStrips[i].IsFadePlanned())
                                allStairsAreOff = false;
                            else
                                ledStrips[i].Fade(0, i * this
                                    .delayForNextStairToSwitchOn);
                        }
                    }
                    else if (state == STAIRS_GO_DOWN)
                    {
                        for (int i = 0; i < stairsCount; ++i)
                        {
                            if (ledStrips[stairsCount - i - 1].IsFadePlanned())
                                allStairsAreOff = false;
                            else
                                ledStrips[stairsCount - i - 1]
                                    .Fade(0, i * this.delayForNextStairToSwitchOn);
                        }
                    }
                    else if (state == STAIRS_GO_UP_AND_DOWN)
                    {
                        int middleStair = stairsCount / 2;

                        for (int i = middleStair; i >= 0; --i)
                        {
                            if (ledStrips[i].IsFadePlanned())
                                allStairsAreOff = false;
                            else
                            {
                                if (ledStrips[i].GetCurrentBrightness() > ledStrips[i].GetMinLevelPwm())
                                {
                                    ledStrips[i]
                                        .Fade(0, (middleStair - i) * this.delayForNextStairToSwitchOn);
                                }
                            }

                            if (ledStrips[stairsCount - i - 1].IsFadePlanned())
                                allStairsAreOff = false;
                            else
                            {
                                if (ledStrips[stairsCount - i - 1].GetCurrentBrightness() > ledStrips[stairsCount - i - 1].GetCurrentBrightness())
                                {
                                    ledStrips[stairsCount - i - 1]
                                        .Fade(0, (middleStair - i) * this.delayForNextStairToSwitchOn);
                                }
                            }
                        }
                    }

                    if (allStairsAreOff)
                        this.state = STAIRS_OFF;
                }
            }
        }

        public void SetMinLevel(int minLevel)
        {
            for (int i = 0; i < this.stairsCount; i++)
                this.ledStrips[i].SetMinLevel(minLevel);
        }

        public void SetMaxLevel(int maxLevel)
        {
            for (int i = 0; i < this.stairsCount; i++)
                this.ledStrips[i].SetMaxLevel(maxLevel);
        }
    }
}
