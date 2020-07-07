package com.b4dnetwork.extensions;

import android.app.Activity;
import android.content.Context;
import com.facebook.ads.*;
import android.util.Log;

public class JFacebookAds{

    public static String DoStuff() {
        return "Message From Java!";
    }

    public String Fuck(){
        return "hahahah";
    }

    // public void Initialize(Context context){
    //     AudienceNetworkAds.initialize(context);
    // }

    // public void LoadInterstitial(Context context, String placementId){
    //     InterstitialAd interstitialAd = new InterstitialAd(context,placementId);
    //     String TAG = "def-fb-ads";

    //     // // interstitial ad listener
    //     // interstitialAd.setAdListener(new InterstitialAdListener() {
    //     //     @Override
    //     //     public void onInterstitialDisplayed(Ad ad) {
    //     //         // Interstitial ad displayed callback
    //     //         Log.e(TAG, "Interstitial ad displayed.");
    //     //     }

    //     //     @Override
    //     //     public void onInterstitialDismissed(Ad ad) {
    //     //         // Interstitial dismissed callback
    //     //         Log.e(TAG, "Interstitial ad dismissed.");
    //     //     }

    //     //     @Override
    //     //     public void onError(Ad ad, AdError adError) {
    //     //         // Ad error callback
    //     //         Log.e(TAG, "Interstitial ad failed to load: " + adError.getErrorMessage());
    //     //     }

    //     //     @Override
    //     //     public void onAdLoaded(Ad ad) {
    //     //         // Interstitial ad is loaded and ready to be displayed
    //     //         Log.d(TAG, "Interstitial ad is loaded and ready to be displayed!");
    //     //         // Show the ad
    //     //         interstitialAd.show();
    //     //     }

    //     //     @Override
    //     //     public void onAdClicked(Ad ad) {
    //     //         // Ad clicked callback
    //     //         Log.d(TAG, "Interstitial ad clicked!");
    //     //     }

    //     //     @Override
    //     //     public void onLoggingImpression(Ad ad) {
    //     //         // Ad impression logged callback
    //     //         Log.d(TAG, "Interstitial ad impression logged!");
    //     //     }
    //     // });

    //     // // For auto play video ads, it's recommended to load the ad
    //     // // at least 30 seconds before it is shown
    //     // interstitialAd.loadAd();
                
    // }


}