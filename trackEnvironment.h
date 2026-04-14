class TrackEnvironment
{
private:
    float trackTemperature;
    float timeOfDayHours;
    bool isNightTime;
    TrackEnvironment();

public:
    /* (&) toto je reference - dava programu garanci ze objekt
    neodkazuje do prazna narozdil od * */
    static TrackEnvironment &getInstance();

    float getTrackTemp();
    bool checkIsNight();
    void advanceTime(float hours);
};