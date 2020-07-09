package com.b4dnetwork.extensions;

import android.util.Log;
import android.app.Activity;
import android.content.Context;

import com.facebook.ads.*;


public class JFacebookAds{
    private String TAG = "defold";
    private Activity activity;

    private InterstitialAd FbInterstitialAd;

    public JFacebookAds(Activity activity){
        this.activity = activity;
    }


    public String Public(String text){
        return text;
    }

    public void Initialize(Activity activity){
        AudienceNetworkAds.initialize(activity);
        //Log.e("FBADS", "Initialize.............");
    }

    public void LoadInterstitial(Activity activity, String placementId){
        
        FbInterstitialAd = new InterstitialAd(activity,placementId);
         
        activity.runOnUiThread(new Runnable() {
            @Override public void run() {
                
                //interstitial ad listener
                FbInterstitialAd.setAdListener(new InterstitialAdListener() {
                    @Override
                    public void onInterstitialDisplayed(final Ad ad) {
                        // Interstitial ad displayed callback
                        Log.e(TAG, "Interstitial ad displayed.");
                    }
                    
                    @Override
                    public void onInterstitialDismissed(final Ad ad) {
                        // Interstitial dismissed callback
                        Log.e(TAG, "Interstitial ad dismissed.");
                        FbInterstitialAd.loadAd(); // load the interstitial , so we can use it again.
                    }
                    @Override
                    public void onError(final Ad ad, final AdError adError) {
                        // Ad error callback
                        Log.e(TAG, "Interstitial ad failed to load: " + adError.getErrorMessage());
                    }
        
                    @Override
                    public void onAdLoaded(final Ad ad) {
                        // Interstitial ad is loaded and ready to be displayed
                        Log.e(TAG, "Interstitial ad is loaded and ready to be displayed!");
                        // switch lodaing signal to true
                        FbInterstitialAd.show();
                        
                    }
                    @Override
                    public void onAdClicked(final Ad ad) {
                        // Ad clicked callback
                        Log.e(TAG, "Interstitial ad clicked!");
                    }
                    @Override
                    public void onLoggingImpression(final Ad ad) {
                        // Ad impression logged callback
                        Log.e(TAG, "Interstitial ad impression logged!");
                    }
                }); 
                FbInterstitialAd.loadAd();
            }
        });

                
    }


}