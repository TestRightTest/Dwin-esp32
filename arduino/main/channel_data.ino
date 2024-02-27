//#define NUM_OF_CHANNELS                 16
//
//
//enum ChannelState {
//    NOT_STARTED,
//    IN_PROGRESS,
//    COMPLETED,
//    HALTED,
//    FAILED
//};
//
//struct ChannelData {
//  String channelName;
//  
//  int firstReading;
//  int redBaseline;
//  int irBaseline;
//
//  String startDateTime;
//  uint8_t progress;
//  ChannelState state;
//
//  // Time 
//  unsigned long startTime;
//  unsigned long endTime;
//  unsigned long decolorTime;
//};
//
//ChannelData channelsData[NUM_OF_CHANNELS];
//
//void initChannel(unsigned channel)
//{
//    memset(channelsData + channel, 0, sizeof(struct ChannelData));
//}
//
//struct ChannelData *getChannel(unsigned channel)
//{
//    return channelsData + channel;    
//}
