#ifndef MUSICDOWNLOADWYINTERFACE_H
#define MUSICDOWNLOADWYINTERFACE_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2017 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "musicobject.h"
#include "musicglobaldefine.h"

///////////////////////////////////////////////////////////////////////////
const QString WY_UA_URL_1          = "OVFtd3M5b05LWFArWFQ5K1MxWk9IdldPSzZCcWRRK3FtNnVCbjExMERDbWhuNTFPWUdJZ2NWMG1ISUdLZjYrRFNwMUVmUUh5WnRpU3haaVdRcklzaEtVZTcxQzMrQldoRGl5bU1DTHIwZElKUW52M3hWc1UvSGVJbE5Hb01hWXI2Q3FDRDFtWmg0VWRYTURtVkd1Um1sdDY0Ykk9";
///////////////////////////////////////////////////////////////////////////
const QString WY_BASE_URL          = "MVNVTXo4bW9WdHhXR1dXeTZmU3k5dmFOcGlua1VOMlE=";
const QString WY_ENCRYPT_STRING    = "3go8&$8*3*3h0k(2)2";
const QString WY_SECKRY            = "411571dca16717d9af5ef1ac97a8d21cb740329890560688b1b624de43f49fdd7702493835141b06ae45f1326e264c98c24ce87199c1a776315e5f25c11056b02dd92791fcc012bff8dd4fc86e37888d5ccc060f7837b836607dbb28bddc703308a0ba67c24c6420dd08eec2b8111067486c907b6e53c027ae1e56c188bc568e";
///////////////////////////////////////////////////////////////////////////
const QString WY_SONG_SEARCH_URL   = "b2dKQmJVWmxNRXlqYU1saWFpbXV5Y1NkenZvN29UVFh4WjhScXpST0Nic3VDNDJkZ0QrWUxnPT0=";
const QString WY_SONG_SQUERY_URL   = "UUs1NUMwUk9yeExmUFVCakUrS29NNm5OQ05lYUV3ZzJPS3NLVW9lZXhNaGwrd2Za";
const QString WY_SONG_MV_NDT_URL   = "dmt4VnNDdWErYjRYUXBnOWdubVBIQT09";
const QString WY_SONG_MV_N_URL     = "dFowcHhjYXk3UWRkZlo2eW40NkY2TEU4VzRoMC84TFh4Wm93N1hCbWk5V21WQnZnYzIrVUhvYmVtK0xtUW90cGpidHBqdz09";
const QString WY_SONG_PATH_URL     = "SXZWVUpDL0FCM1pUODJsaDNGZjN4OFlVZk1JQzdXOXRpWVJTSTVEUEZJZkI3YUJOMUdLQ3lnPT0=";
const QString WY_SONG_LRC_URL      = "TjNjL2ttNVR4cGluaEpwU1B2VzNucFhEWUdkRERkempFcThjWEIvMzMzMzVjaWVoR3ZNYXN5MHZsOE9sMTQ1TG1yeDNVQT09";
const QString WY_SONG_INFO_URL     = "N2NkQWg4V3o0NXYvMlFHamVOWVZ5Y2NnTDk2cTNFdFVROVNwTndJV2REYXM0K01Yd2NIT1pwaGcyTGJ0QVVsNHVxT0lTZHFKNTI2QnlWMnVBWFNDdWYrb09Waz0=";
const QString WY_SONG_INFO_NDT_URL = "ei9SdFJqZWlHWlh3eXBsWHJTS09FbUpRU1J4Zi9wZDlOQUMyVTVnL3c0YW9GSjVH";
const QString WY_SONG_INFO_N_URL   = "M21IV2dlSHNzaE1zZEpyb2hrQ0dqVEY3Ly9DZ3ZteDM1RStuSlJIRVVCRTljbWJKKzRBVnNZY3JEcEZKY045dEJ5KzM0WHArSDVCYXhrMHBoZmlTZXBWdHIvND0=";
const QString WY_SG_DETAIL_NDT_URL = "RWxCUVNVa3NORGFrTUE3SzVOSmJxTC9YMVByVTA4SHVLNHFHUGI1R1hVdz0=";
const QString WY_SG_DETAIL_N_URL   = "S3paVUxRY3hZVDVweWhJZFU0K0FpakhJc3R5YW1hbmpmRUVsL3JTRUdwcnlDdDlMWFJSR0ludFFPZ1MycWExVVlLNjg5Njh3VmV2cGxpQzE=";
///////////////////////////////////////////////////////////////////////////
const QString WY_AR_N_URL          = "YmhRbVZDYy8rbytiRWc5cXc2MUVUdEFKRmw2eFhTVmhqWTZ6MmRVNEMzbVg0Q3BFQVF4d0VYUktBMk1aVUNVb3ZaNk5VL3BYRjBZPQ==";
const QString WY_AR_INFO_NDT_URL   = "dmt4VnNDdWErYjRYUXBnOWdubVBIQT09";
const QString WY_AR_INFO_N_URL     = "RnJtNVNTT01ncFI2cDJMRTMrSFFwWFBWVEEzQnZNYmg4TEJrRjZCeHorTE13aVNCNUxScGo2QzNzVUNKNzhKbkI2VjNKUT09";
///////////////////////////////////////////////////////////////////////////
const QString WY_ALBUM_N_URL       = "QzJrMDNKTGlpVHpvY2taYm5BSWZGVTZWM09xYW5STDdXRFE5eTEzczhLZHB1RWljWlIxOVhRUXVDcmpuVjJsQnhqcmZRZE9UU0JZPQ==";
///////////////////////////////////////////////////////////////////////////
const QString WY_SG_TOPLIST_NDT_URL= "dmt4VnNDdWErYjRYUXBnOWdubVBIQT09";
const QString WY_SG_TOPLIST_N_URL  = "VUdTa0xMeG1Nblc4cThoS2E1QzhJK0lrTHJBRmk4TUJZMC9NQW1GanZydDJmR0VJVVRZNmJQSEhOZU96aE55bTJxdW55RldJOHl6aElNdTlHbkZkSmc9PQ==";
///////////////////////////////////////////////////////////////////////////
const QString WY_COMMIT_NDT_URL    = "cmVkanJSR0J1UGdWVlAwaSs2bVFSeTFMdVhvQzVHNVgyWUVGSWFESXgyUXlSNkU5KzhqQXlBdlI1b3h0UmI5N3lUZlVBM2NIZTE2Tk4zV2Y=";
const QString WY_SG_COMMIT_N_URL   = "VjJRaU8vR2xYZmIxM0RIMUNxU2NJRzlLSDVqZTY5ZVVXNlhUWndSWkc1TmlEajFKaGRwaS9TRThKRCtyL0Z4SWVSWmovSzhqMzFKV1R3QmxwUVBHSzA5ZGx0d2VmN0JMaVRFaVRnPT0=";
///////////////////////////////////////////////////////////////////////////
const QString WY_PL_COMMIT_N_URL   = "aURTWlNhUlJISEc3VmExQ2FsUXZqS1lXOVdGSzBOc3dmaHNMK3M0U2tScnNIdHc3Y2NJSGJBVVhhUTc1eHIrNEJrdmgzUlpCOU96UmNsZEEwbnIvQkZQU0tFZU9oY0JKazNlRWZRPT0=";
const QString WY_PL_NDT_URL        = "SDBaSmFYMlhNdk50TFZ4VkNFY1dRUDdtYk9icVAvOWwveCtXWXliZVVjQmFHeXBwdnp3LzJnWjB2cVlBeG1uV0VKTkNScVR2c3ROQmtQRjVVcFIyZWRRVkVFRkFSQlphVGlxeTU3Z0tRT2s9";
const QString WY_PL_N_URL          = "aFZGMG5CbXZXNmNGaS9jZEV6S0c2RE53Tm5Ud3I3WGJSS2ErQVQ5RjdYRlhUMENuS25yRnYwVHUzMnIrQUJQaFRVTlMrSTJUM1pNPQ==";
const QString WY_PL_ATTR_NDT_URL   = "VkpFemFKQWtOY2ZXeUNpZ210VjVGYndOZ2VibUZlZHV6amZJaE5VL1czaWFzRkNqV2lYKy9CR29McXl6LzUrUldWcmtKS0Fjb0s5dFBFeXpCaHRCc1dhYlp1bGd3U1ZY";
const QString WY_PL_ATTR_N_URL     = "VUdTa0xMeG1Nblc4cThoS2E1QzhJK0lrTHJBRmk4TUJZMC9NQW1GanZydDJmR0VJVVRZNmJQSEhOZU96aE55bTJxdW55RldJOHl6aElNdTlHbkZkSmc9PQ==";
///////////////////////////////////////////////////////////////////////////

class QNetworkRequest;

/*! @brief The class to wangyi query download interface.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadWYInterface
{
public:
    /*!
     * Make token query url string.
     */
    void makeTokenQueryQequest(QNetworkRequest *request);
    /*!
     * Make token query url string.
     */
    QByteArray makeTokenQueryUrl(QNetworkRequest *request, const QString &query, const QString &type);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttribute(MusicObject::MusicSongInformation *info, int bitrate);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttribute(MusicObject::MusicSongInformation *info, const QVariantMap &key, int bitrate);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttribute(MusicObject::MusicSongInformation *info, const QVariantMap &key,
                                    const QString &quality, bool all);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttributeNew(MusicObject::MusicSongInformation *info, int bitrate);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttributeNew(MusicObject::MusicSongInformation *info, const QVariantMap &key, int bitrate);
    /*!
     * Read tags(size\bitrate\url) from query results.
     */
    void readFromMusicSongAttributeNew(MusicObject::MusicSongInformation *info, const QVariantMap &key,
                                       const QString &quality, bool all);
    /*!
     * Encrypted music info id.
     */
    QString encryptedId(qlonglong id);
    /*!
     * Encrypted music info id.
     */
    QString encryptedId(const QString &string);

};

#endif // MUSICDOWNLOADWYINTERFACE_H