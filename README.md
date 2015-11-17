### LinJam Is Not .... - Oh wait, Yes it is!<br />LinJam is linear NINJAM
![LinJam screenshot](http://teamstream.herokuapp.com/linjam.png)
| build | status |
| ----  | ------ |
| linux | [![Build Status](https://travis-ci.org/linjam/linjam.svg?branch=linux)](https://travis-ci.org/linjam/linjam) |
| dev   | [![Build Status](https://travis-ci.org/linjam/linjam.svg)](https://travis-ci.org/linjam/linjam) |

#### Get LinJam
###### LinJam for windows
* coming soon (get the source for now)

###### LinJam for penguins
```
  # subscribe to the repository
  $ curl -s https://packagecloud.io/install/repositories/ninjam/ninjam/script.deb.sh | sudo bash

  # install the package
  $ sudo apt-get install linjam
```

###### LinJam for apples
* coming soon (get the source for now)

#### About LinJam

LinJam is a cross-platform NINJAM client utilizing the [libninjam library](https://github.com/libninjam/libninjam) and built upon the JUCE framework.  It is the much needed modern replacement for the aging platform-specific clients with many new enhancements.

The highest goal of the LinJam project (and it's predecessor TeamStream) is to flatten the pro-audio learning-curve; easing the intimidation that most non-technical musicians experience when they are first introduced to NINJAM.  Some of the ways proposed to accomplish this include: offering a minimal interface with some reasonable default settings, some normalizing/conditioning features such as auto-gain and limiter, and the option to elect a "sound man" to actively set levels for other peers (especially the bot which streams and posts its mixdown to the web).  It is hoped that these, along with the convenience features introduced with TeamStream, will encourage musicians without prior experience in audio production (which today is essentially a pre-requisite) to engage with the bliss that is NINJAM.

#### Development Status

The first milestone (cross-platform NINJAM 0.06 equivalent) is now 90% complete ([see the roadmap here](https://github.com/linjam/linjam/milestones/cross-platform%20NINJAM%200.06%20equivalent)).  The GNU/Linux and Windows builds are quite functional; with only some minor details and cosmetics remaining to be addressed.  The current implementation targets MacOS also; which has not yet been built but should be viable with a bit of tweaking and testing.  Please let us know if you have successfully compiled LinJam on a Mac.

This implementation (thanks @ Jules for his excellent JUCE framework) is more stable and efficient than the original TeamStream (based on NINJAM for Windows); and is already quite nicer looking even with the default widgets.  The JUCE framework also opens up the possibility of supporting several other platforms such as Android, IOS, and even Mozilla/Firefox and VST plugins, all with the same codebase.

LinJam will eventually incorperate all of the features of [TeamStream](http://teamstream.herokuapp.com) which allows free-form linear chain-streaming in addition to the standard NINJAM synced broadcast mode; and features several usability enhancements such as one-click voting, one-click joining via the web, and cross-room/cross-server jammers list.  This will be the second milestone (cross-platform TeamStream 0.7.0 equivalent) ([see the roadmap here](https://github.com/linjam/linjam/milestones/cross-platform%20TeamStream%200.7.0%20equivalent)).  Read more about the linear chain-streaming mode on the [About TeamStream](http://teamstream.herokuapp.com/about.html) page.  After this, some more sophisticated backend-supported features (such as shared chord charts) may be implemented with the co-operation of the libninjam team.

#### Why the name change?

Because, although team-streaming is the most descriptive term for the most distinguishing functionality of this program; a web search for "teamstream" is polluted with numerous brands past and present using some form of the name "TeamStream", which has been trade-marked and abandoned by multiple entities over the years.  It is apparently a popular name to adopt and discard.  Also, LinJam is a completely new client; written from scratch and resembling TeamStream only in spirit and functionality.
