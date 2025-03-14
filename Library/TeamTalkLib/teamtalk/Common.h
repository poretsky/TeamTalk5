/*
 * Copyright (c) 2005-2018, BearWare.dk
 * 
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Kirketoften 5
 * DK-8260 Viby J
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk SDK owned by
 * BearWare.dk. Use of this file, or its compiled unit, requires a
 * TeamTalk SDK License Key issued by BearWare.dk.
 *
 * The TeamTalk SDK License Agreement along with its Terms and
 * Conditions are outlined in the file License.txt included with the
 * TeamTalk SDK distribution.
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <TeamTalkDefs.h>
#include <codec/MediaUtil.h>

#if defined(ENABLE_WEBRTC)
#include <avstream/WebRTCPreprocess.h>
#endif

#include <myace/MyACE.h>

#include <ace/INET_Addr.h>
#include <ace/Time_Value.h>

#include <map>
#include <vector>
#include <set>

namespace teamtalk {

    enum ServerLogEvent
    {
        SERVERLOGEVENT_NONE                        = 0x00000000,
        SERVERLOGEVENT_USER_CONNECTED              = 0x00000001,
        SERVERLOGEVENT_USER_DISCONNECTED           = 0x00000002,
        SERVERLOGEVENT_USER_LOGGEDIN               = 0x00000004,
        SERVERLOGEVENT_USER_LOGGEDOUT              = 0x00000008,
        SERVERLOGEVENT_USER_LOGINFAILED            = 0x00000010,
        SERVERLOGEVENT_USER_TIMEDOUT               = 0x00000020,
        SERVERLOGEVENT_USER_KICKED                 = 0x00000040,
        SERVERLOGEVENT_USER_BANNED                 = 0x00000080,
        SERVERLOGEVENT_USER_UNBANNED               = 0x00000100,
        SERVERLOGEVENT_USER_UPDATED                = 0x00000200,
        SERVERLOGEVENT_USER_JOINEDCHANNEL          = 0x00000400,
        SERVERLOGEVENT_USER_LEFTCHANNEL            = 0x00000800,
        SERVERLOGEVENT_USER_MOVED                  = 0x00001000,
        SERVERLOGEVENT_USER_TEXTMESSAGE_PRIVATE    = 0x00002000,
        SERVERLOGEVENT_USER_TEXTMESSAGE_CUSTOM     = 0x00004000,
        SERVERLOGEVENT_USER_TEXTMESSAGE_CHANNEL    = 0x00008000,
        SERVERLOGEVENT_USER_TEXTMESSAGE_BROADCAST  = 0x00010000,
        SERVERLOGEVENT_CHANNEL_CREATED             = 0x00020000,
        SERVERLOGEVENT_CHANNEL_UPDATED             = 0x00040000,
        SERVERLOGEVENT_CHANNEL_REMOVED             = 0x00080000,
        SERVERLOGEVENT_FILE_UPLOADED               = 0x00100000,
        SERVERLOGEVENT_FILE_DOWNLOADED             = 0x00200000,
        SERVERLOGEVENT_FILE_DELETED                = 0x00400000,
        SERVERLOGEVENT_SERVER_UPDATED              = 0x00800000,
        SERVERLOGEVENT_SERVER_SAVECONFIG           = 0x01000000,
        SERVERLOGEVENT_USER_CRYPTERROR             = 0x02000000,

        /*
        SERVERLOGEVENT_NEXT                        = 0x04000000,
        */

        SERVERLOGEVENT_DEFAULT                     = 0x03FFFFFF,
    };

    typedef uint32_t ServerLogEvents;

    struct ServerProperties
    {
        ACE_TString systemid;
        ACE_TString version;
        bool autosave = false;;
        ACE_TString motd;
        ACE_TString servername;
        int maxusers = 0;
        int maxloginattempts = 0; //max login attempts with wrong password
        int max_logins_per_ipaddr = 0;
        int logindelay = 0; // msec before IP-address can log in again
        ACE_INT64 diskquota = 0; //max bytes for each channel to store files
        ACE_INT64 maxdiskusage = 0; //max bytes to use for storage of files
        int usertimeout = 0;
        int voicetxlimit = 0;
        int videotxlimit = 0;
        int mediafiletxlimit = 0;
        int desktoptxlimit = 0;
        int totaltxlimit = 0;
        ServerLogEvents logevents = SERVERLOGEVENT_NONE;
        ServerProperties();
    };

    struct ServerStats
    {
        ACE_INT64 total_bytessent = 0;
        ACE_INT64 total_bytesreceived = 0;
        ACE_INT64 last_bytessent = 0;
        ACE_INT64 last_bytesreceived = 0;
        ACE_INT64 avg_bytessent = 0;
        ACE_INT64 avg_bytesreceived = 0;
        ACE_INT64 voice_bytesreceived = 0;
        ACE_INT64 voice_bytessent = 0;
        ACE_INT64 last_voice_bytessent = 0;
        ACE_INT64 vidcap_bytesreceived = 0;
        ACE_INT64 vidcap_bytessent = 0;
        ACE_INT64 last_vidcap_bytessent = 0;
        ACE_INT64 mediafile_bytesreceived = 0;
        ACE_INT64 mediafile_bytessent = 0;
        ACE_INT64 last_mediafile_bytessent = 0;
        ACE_INT64 desktop_bytesreceived = 0;
        ACE_INT64 desktop_bytessent = 0;
        ACE_INT64 last_desktop_bytessent = 0;
        ACE_INT64 files_bytesreceived = 0;
        ACE_INT64 files_bytessent = 0;

        int userspeak = 0;
        int usersservered = 0;
        //uptime
        ACE_Time_Value starttime;
        
        ACE_INT64 packets_received = 0, packets_sent = 0; // only used internally

        ServerStats() { }
    };

    /* Remember to updated DLL header file when modifying this */
    enum MsgType
    {
        TTNoneMsg       = 0,
        TTUserMsg       = 1,
        TTChannelMsg    = 2,
        TTBroadcastMsg  = 3,
        TTCustomMsg     = 4
    };

    //text messages for server and client
    struct TextMessage
    {
        MsgType msgType = TTNoneMsg;
        int from_userid = 0;
        ACE_TString from_username;
        int to_userid = 0;
        ACE_TString content;
        int channelid = 0;
        bool more = false;
    };

    /* Remember to updated DLL header file when modifying this */
    enum UserType
    {
        USERTYPE_NONE         = 0x00,
        USERTYPE_DEFAULT      = 0x01,
        USERTYPE_ADMIN        = 0x02,
    };

    typedef ACE_UINT32 UserTypes;

    /* Remember to updated DLL header file when modifying this */
    enum UserRight
    {
        USERRIGHT_NONE                                  = 0x00000000,
        USERRIGHT_MULTI_LOGIN                           = 0x00000001,
        USERRIGHT_VIEW_ALL_USERS                        = 0x00000002,
        USERRIGHT_CREATE_TEMPORARY_CHANNEL              = 0x00000004,
        USERRIGHT_MODIFY_CHANNELS                       = 0x00000008,
        USERRIGHT_TEXTMESSAGE_BROADCAST                 = 0x00000010,
        USERRIGHT_KICK_USERS                            = 0x00000020,
        USERRIGHT_BAN_USERS                             = 0x00000040,
        USERRIGHT_MOVE_USERS                            = 0x00000080,
        USERRIGHT_OPERATOR_ENABLE                       = 0x00000100,
        USERRIGHT_UPLOAD_FILES                          = 0x00000200,
        USERRIGHT_DOWNLOAD_FILES                        = 0x00000400,
        USERRIGHT_UPDATE_SERVERPROPERTIES               = 0x00000800,
        USERRIGHT_TRANSMIT_VOICE                        = 0x00001000,
        USERRIGHT_TRANSMIT_VIDEOCAPTURE                 = 0x00002000,
        USERRIGHT_TRANSMIT_DESKTOP                      = 0x00004000,
        USERRIGHT_TRANSMIT_DESKTOPINPUT                 = 0x00008000,
        USERRIGHT_TRANSMIT_MEDIAFILE_AUDIO              = 0x00010000,
        USERRIGHT_TRANSMIT_MEDIAFILE_VIDEO              = 0x00020000,
        USERRIGHT_TRANSMIT_MEDIAFILE                    = USERRIGHT_TRANSMIT_MEDIAFILE_AUDIO |
                                                          USERRIGHT_TRANSMIT_MEDIAFILE_VIDEO,
        USERRIGHT_LOCKED_NICKNAME                       = 0x00040000,
        USERRIGHT_LOCKED_STATUS                         = 0x00080000,
        USERRIGHT_RECORD_VOICE                          = 0x00100000,
        USERRIGHT_VIEW_HIDDEN_CHANNELS                  = 0x00200000,
        USERRIGHT_TEXTMESSAGE_USER                      = 0x00400000,
        USERRIGHT_TEXTMESSAGE_CHANNEL                   = 0x00800000,

        USERRIGHT_DEFAULT = USERRIGHT_MULTI_LOGIN |
                            USERRIGHT_VIEW_ALL_USERS |
                            USERRIGHT_CREATE_TEMPORARY_CHANNEL |
                            USERRIGHT_UPLOAD_FILES |
                            USERRIGHT_DOWNLOAD_FILES |
                            USERRIGHT_TRANSMIT_VOICE |
                            USERRIGHT_TRANSMIT_VIDEOCAPTURE |
                            USERRIGHT_TRANSMIT_DESKTOP |
                            USERRIGHT_TRANSMIT_DESKTOPINPUT |
                            USERRIGHT_TRANSMIT_MEDIAFILE |
                            USERRIGHT_TEXTMESSAGE_USER |
                            USERRIGHT_TEXTMESSAGE_CHANNEL,

        USERRIGHT_ALL                       =  0x00FFFFFF ^ (USERRIGHT_LOCKED_NICKNAME | USERRIGHT_LOCKED_STATUS),
        USERRIGHT_KNOWN_MASK                = ~0xFF000000
    };

    typedef ACE_UINT32 UserRights;

    struct Abuse
    {
        int n_cmds = 0;
        int cmd_msec = 0;
        Abuse() { }

        std::vector<int> toParam() const
        {
            std::vector<int> flood;
            flood.push_back(n_cmds);
            flood.push_back(cmd_msec);
            return flood;
        }
        void fromParam(const std::vector<int>& flood)
        {
            if(flood.size()>=2)
            {
                n_cmds = flood[0];
                cmd_msec = flood[1];
            }
        }
    };

    struct UserAccount
    {
        ACE_TString username;
        ACE_TString passwd;
        ACE_TString note;
        UserTypes usertype = USERTYPE_NONE;
        UserRights userrights = USERRIGHT_NONE; /* Mask of UserRight */
        int userdata = 0;
        ACE_TString init_channel;
        intset_t auto_op_channels;
        int audiobpslimit = 0;
        Abuse abuse;
        ACE_TString nickname; /* TODO: add to TT API */
        ACE_Time_Value lastupdated;
        ACE_Time_Value lastlogin;
        
        UserAccount();
        bool IsWebLogin() const;
    };
    typedef std::vector<UserAccount> useraccounts_t;

    enum BanType
    {
        BANTYPE_NONE            = 0x00,
        BANTYPE_CHANNEL         = 0x01,
        BANTYPE_IPADDR          = 0x02,
        BANTYPE_USERNAME        = 0x04,
        BANTYPE_DEFAULT = BANTYPE_IPADDR,
    };
    typedef ACE_UINT32 BanTypes;

    struct BannedUser
    {
        BanTypes bantype;
        ACE_TString ipaddr;
        ACE_TString chanpath;
        ACE_Time_Value bantime;
        ACE_TString nickname;
        ACE_TString username; // banned username
        ACE_TString owner; // who made the ban
        BannedUser() : bantype(BANTYPE_NONE) { bantime = ACE_OS::gettimeofday(); }
        bool Same(const BannedUser& user) const;
        bool Match(const BannedUser& user) const;
    };

    typedef std::vector<BannedUser> bannedusers_t;

    ACE_TString DateToString(const ACE_Time_Value& tv);

    enum StreamType //ensure DLL compliance
    {
        STREAMTYPE_NONE                     = 0x00000000,
        STREAMTYPE_VOICE                    = 0x00000001,
        STREAMTYPE_VIDEOCAPTURE             = 0x00000002,
        STREAMTYPE_MEDIAFILE_AUDIO          = 0x00000004,
        STREAMTYPE_MEDIAFILE_VIDEO          = 0x00000008,
        STREAMTYPE_MEDIAFILE                = STREAMTYPE_MEDIAFILE_AUDIO |
                                              STREAMTYPE_MEDIAFILE_VIDEO,
        STREAMTYPE_DESKTOP                  = 0x00000010,
        STREAMTYPE_DESKTOPINPUT             = 0x00000020,
        STREAMTYPE_CHANNELMSG               = 0x00000040,

        STREAMTYPE_LOCALMEDIAPLAYBACK_AUDIO = 0x00000080,

        STREAMTYPE_ALL                      = 0x0000ffff,
    };

    typedef ACE_UINT32 StreamTypes;


    enum FileTransferStatus
    {
        FILETRANSFER_CLOSED     = 0,
        FILETRANSFER_ERROR      = 1,
        FILETRANSFER_ACTIVE     = 2,
        FILETRANSFER_FINISHED   = 3,
    };

#define TRANSFERKEY_SIZE 16

    struct FileTransfer
    {
        FileTransferStatus status = FILETRANSFER_CLOSED;
        int channelid = 0;
        ACE_TString localfile;
        ACE_TString filename;
        int userid = 0;
        ACE_INT64 filesize = 0;
        ACE_INT64 transferred = 0;
        int transferid = 0;
        bool inbound = true;
        ACE_TString transferkey;
        FileTransfer() { }
    };

    /* Remember to updated DLL header file when modifying this */
    enum Codec
    {
        CODEC_NO_CODEC                  = 0,
        CODEC_SPEEX                     = 1,
        CODEC_SPEEX_VBR                 = 2,
        CODEC_OPUS                      = 3,
        CODEC_WEBM_VP8                  = 128,
    };

    struct SpeexCodec
    {
        int bandmode;
        int quality;
        int frames_per_packet;
        bool sim_stereo;
    };
    
    struct SpeexVBRCodec
    {
        int bandmode;
        int vbr_quality;
        int bitrate;
        int max_bitrate;
        bool dtx;
        int frames_per_packet;
        bool sim_stereo;
    };

    struct OpusCodec
    {
        int samplerate;
        int channels;
        int application;
        int complexity;
        bool fec;
        bool dtx;
        int bitrate;
        bool vbr;
        bool vbr_constraint;
        int frame_size;
        int frames_per_packet;
    };

    struct AudioCodec
    {
        Codec codec;
        union
        {
            SpeexCodec speex;
            SpeexVBRCodec speex_vbr;
            OpusCodec opus;
        };
        AudioCodec()
        {
            //ensure that codecs can be compared using memcmp
            memset(this, 0, sizeof(AudioCodec));
            codec = CODEC_NO_CODEC;
        }
        inline bool operator==(const AudioCodec& ch) const
        {
            switch (codec)
            {
            case CODEC_SPEEX :
                return memcmp(&speex, &ch.speex, sizeof(speex)) == 0;
            case CODEC_SPEEX_VBR :
                return memcmp(&speex_vbr, &ch.speex_vbr, sizeof(speex_vbr)) == 0;
            case CODEC_OPUS :
                return memcmp(&opus, &ch.opus, sizeof(opus)) == 0;
            case CODEC_NO_CODEC :
                return codec == ch.codec;
            case CODEC_WEBM_VP8 :
                return false;
            }
            return false;
        }
        inline bool operator!=(const AudioCodec& ch) const
        {
            return (ch == *this) == false;//memcmp(this, &ch, sizeof(ch));
        }
    };

    struct AudioConfig
    {
        bool enable_agc;
        int gain_level;
        AudioConfig()
            : enable_agc(false)
            , gain_level(0) { }
    };

    struct SpeexDSP
    {
        bool enable_agc = false;
        int agc_gainlevel = 0;
        int agc_maxincdbsec = 0;
        int agc_maxdecdbsec = 0;
        int agc_maxgaindb = 0;
        bool enable_denoise = false;
        int maxnoisesuppressdb = 0;
        bool enable_aec = 0;
        int aec_suppress_level = 0;
        int aec_suppress_active = 0;

        SpeexDSP() { }
    };

    struct TTAudioPreprocessor
    {
        int gainlevel = GAIN_NORMAL;
        bool muteleft = false;
        bool muteright = false;

        TTAudioPreprocessor() { }
    };

    enum AudioPreprocessorType
    {
        AUDIOPREPROCESSOR_NONE      = 0,
        AUDIOPREPROCESSOR_SPEEXDSP  = 1,
        AUDIOPREPROCESSOR_TEAMTALK  = 2,
        AUDIOPREPROCESSOR_WEBRTC_OBSOLETE_R4332    = 3,
        AUDIOPREPROCESSOR_WEBRTC    = 4,
    };
    
    struct AudioPreprocessor
    {
        AudioPreprocessorType preprocessor = AUDIOPREPROCESSOR_NONE;
        union
        {
            SpeexDSP speexdsp;
            TTAudioPreprocessor ttpreprocessor;
        };
#if defined(ENABLE_WEBRTC)
        webrtc::AudioProcessing::Config webrtc;
#endif
        AudioPreprocessor() {}
    };

    struct SoundDeviceEffects
    {
        bool enable_agc = false;
        bool enable_aec = false;
        bool enable_denoise = false;
    };

    struct WebMVP8Codec
    {
        int rc_target_bitrate; /* 0 = 256 kbit/sec */
        unsigned long encode_deadline; /* 0 = VPX_DL_BEST_QUALITY */
    };

    struct VideoCodec
    {
        Codec codec;
        union
        {
            WebMVP8Codec webm_vp8;
        };
        VideoCodec() : webm_vp8()
        {
            codec = CODEC_NO_CODEC;
        }
    };

    struct RemoteFile
    {
        int channelid = 0;
        int fileid = 0;
        ACE_TString filename;
        ACE_TString internalname;
        ACE_INT64 filesize;
        ACE_TString username;
        ACE_Time_Value uploadtime;
        RemoteFile();
    };

    typedef std::vector< RemoteFile > files_t;

    enum RGBMode
    {
        BMP_NONE            = 0,
        BMP_RGB8_PALETTE    = 1,
        BMP_RGB16_555       = 2,
        BMP_RGB24           = 3,
        BMP_RGB32           = 4
    };

    enum DesktopProtocol
    {
        DESKTOPPROTOCOL_NONE    = 0,
        DESKTOPPROTOCOL_ZLIB_1  = 1
    };

    struct DesktopWindow
    {
        int session_id;
        int width;
        int height;
        RGBMode rgb_mode;
        DesktopProtocol desktop_protocol;
        DesktopWindow()
            : session_id(0)
            , width(0)
            , height(0)
            , rgb_mode(BMP_NONE)
            , desktop_protocol(DESKTOPPROTOCOL_NONE)
        {}
        DesktopWindow(int s_id, int w, int h, RGBMode mode, 
                      DesktopProtocol dskproto)
            : session_id(s_id)
            , width(w)
            , height(h)
            , rgb_mode(mode)
            , desktop_protocol(dskproto)
        {}
    };


    /* Remember to updated DLL header file when modifying this */
    enum ChannelType
    {
        CHANNEL_DEFAULT             = 0x0000,
        CHANNEL_PERMANENT           = 0x0001,
        CHANNEL_SOLO_TRANSMIT       = 0x0002,
        CHANNEL_CLASSROOM           = 0x0004,
        CHANNEL_OPERATOR_RECVONLY   = 0x0008,
        CHANNEL_NO_VOICEACTIVATION  = 0x0010,
        CHANNEL_NO_RECORDING        = 0x0020,
        CHANNEL_HIDDEN              = 0x0040,
    };

    typedef ACE_UINT32 ChannelTypes;

    typedef std::map< StreamType, std::set<int> > transmitusers_t;

    struct ChannelProp
    {
        ACE_TString name;
        ACE_TString passwd;
        ACE_TString topic;
        ACE_TString oppasswd;
        ACE_INT64 diskquota = 0;
        int maxusers = MAX_USERS_IN_CHANNEL;
        bool bProtected = false;
        std::set<int> setops;
        int channelid = 0;
        int parentid = 0;
        AudioCodec audiocodec;
        AudioConfig audiocfg;
        files_t files;
        ChannelTypes chantype = CHANNEL_DEFAULT;
        ACE_UINT32 chankey = 0;
        int userdata = 0;
        transmitusers_t transmitusers;
        std::vector<int> transmitqueue;
        int transmitswitchdelay = 0;
        int totvoice = 0, totmediafile = 0;
        bannedusers_t bans;
        std::set<int> GetTransmitUsers(StreamType st) const
        {
            if(transmitusers.find(st) != transmitusers.end())
                return transmitusers.at(st);
            return std::set<int>();
        }

        ChannelProp()
        {
            memset(&audiocodec, 0, sizeof(audiocodec));
            audiocodec.codec = CODEC_NO_CODEC;

            // ensure we can use std::map<>.at()
            transmitusers[STREAMTYPE_VOICE] = std::set<int>();
            transmitusers[STREAMTYPE_VIDEOCAPTURE] = std::set<int>();
            transmitusers[STREAMTYPE_DESKTOP] = std::set<int>();
            transmitusers[STREAMTYPE_MEDIAFILE] = std::set<int>();
            transmitusers[STREAMTYPE_CHANNELMSG] = std::set<int>();
        }
    };

    enum KeyState
    {
        KEYSTATE_NONE       = 0x00000000,
        KEYSTATE_DOWN       = 0x00000001,
        KEYSTATE_UP         = 0x00000002,
    };

    typedef ACE_UINT32 KeyStateMask;

    struct DesktopInput
    {
        ACE_UINT16 x = -1;
        ACE_UINT16 y = -1;
        ACE_UINT32 keycode = -1;
        KeyStateMask keystate = KEYSTATE_NONE;
        DesktopInput() { }
    };

    /* Remember to updated DLL header file when modifying this */
    enum AudioFileFormat
    {
        AFF_NONE                 = 0,
        AFF_CHANNELCODEC_FORMAT  = 1,
        AFF_WAVE_FORMAT          = 2,
        AFF_MP3_16KBIT_FORMAT    = 3,
        AFF_MP3_32KBIT_FORMAT    = 4,
        AFF_MP3_64KBIT_FORMAT    = 5,
        AFF_MP3_128KBIT_FORMAT   = 6,
        AFF_MP3_256KBIT_FORMAT   = 7,
        AFF_MP3_320KBIT_FORMAT   = 8,
    };

    int AFFToMP3Bitrate(AudioFileFormat aff);

    /* Remember to updated DLL header file when modifying this */
    enum MediaFileStatus
    {
        MFS_CLOSED      = 0,
        MFS_ERROR       = 1,
        MFS_STARTED     = 2,
        MFS_FINISHED    = 3,
        MFS_ABORTED     = 4,
        MFS_PAUSED      = 5,
        MFS_PLAYING     = 6
    };

    /* Remember to updated DLL header file when modifying this.
     * If more than 16 bits ServerUser subscription model will be broken. */
    enum
    {
        SUBSCRIBE_NONE                                  = 0x00000000,
        SUBSCRIBE_USER_MSG                              = 0x00000001,
        SUBSCRIBE_CHANNEL_MSG                           = 0x00000002,
        SUBSCRIBE_BROADCAST_MSG                         = 0x00000004,
        SUBSCRIBE_CUSTOM_MSG                            = 0x00000008,

        SUBSCRIBE_VOICE                                 = 0x00000010,
        SUBSCRIBE_VIDEOCAPTURE                          = 0x00000020,
        SUBSCRIBE_DESKTOP                               = 0x00000040,
        SUBSCRIBE_DESKTOPINPUT                          = 0x00000080,
        SUBSCRIBE_MEDIAFILE                             = 0x00000100,

        SUBSCRIBE_ALL                                   = 0x000001FF,

        SUBSCRIBE_LOCAL_DEFAULT = (SUBSCRIBE_USER_MSG |
                                   SUBSCRIBE_CHANNEL_MSG |
                                   SUBSCRIBE_BROADCAST_MSG |
                                   SUBSCRIBE_CUSTOM_MSG |
                                   SUBSCRIBE_MEDIAFILE),
        SUBSCRIBE_PEER_DEFAULT = (SUBSCRIBE_ALL & ~SUBSCRIBE_DESKTOPINPUT),


        SUBSCRIBE_INTERCEPT_USER_MSG                    = 0x00010000,
        SUBSCRIBE_INTERCEPT_CHANNEL_MSG                 = 0x00020000,
        /*SUBSCRIBE_INTERCEPT_BROADCAST_MSG             = 0x00040000, */
        SUBSCRIBE_INTERCEPT_CUSTOM_MSG                  = 0x00080000,

        SUBSCRIBE_INTERCEPT_VOICE                       = 0x00100000,
        SUBSCRIBE_INTERCEPT_VIDEOCAPTURE                = 0x00200000,
        SUBSCRIBE_INTERCEPT_DESKTOP                     = 0x00400000,
        /*SUBSCRIBE_INTERCEPT_DESKTOPINPUT              = 0x00800000, */
        SUBSCRIBE_INTERCEPT_MEDIAFILE                   = 0x01000000,

        SUBSCRIBE_INTERCEPT_ALL                         = 0x017B0000,
    };

    typedef ACE_UINT32 Subscriptions;

    std::vector<int> ConvertFrameSizes(const std::vector<uint16_t>& in);
    int SumFrameSizes(const std::vector<uint16_t>& in);
    std::vector<uint16_t> ConvertFrameSizes(const std::vector<int>& in);
    int SumFrameSizes(const std::vector<int>& in);

#define TRANSMITUSERS_FREEFORALL 0xFFF

#define PACKETNO_GEQ(a,b) ((int16_t)((a)-(b)) >= 0)
#define STREAMID_GT(a,b) ((int8_t)((a)-(b)) > 0)
#define SESSIONID_GEQ(a,b) ((int8_t)((a)-(b)) >= 0)
}
#endif
