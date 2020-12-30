package com.b4dnetwork.extensions;

import android.util.Log;
import android.app.Activity;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.facebook.ads.*;


public class JFacebookAds{


    private final String TAG = "defold";
    private Activity activity;

    private InterstitialAd FbInterstitialAd;
    private RewardedVideoAd FbRewardedVideoAd;
    private AdView AdView; // banner Ad



    private LinearLayout linearLayout = null;
    private LinearLayout.LayoutParams linearLayoutParams = null;
    private WindowManager windowManager;
    private WindowManager.LayoutParams windowManagerParams = null;


    //Ads Signals
    private boolean isInterstitialLoaded , isRewardedLoaded , isBannerShown , isBannerLoaded = false;


    public JFacebookAds(Activity activity){
        this.activity = activity;
    }



    public void Initialize(Activity activity){
        AudienceNetworkAds.initialize(activity);
    }


    /**
     * Load a interstitial ad
     * @param placementId interstitial ad
     */
    public void LoadInterstitial(String placementId){

        FbInterstitialAd = new InterstitialAd(activity,placementId);

        InterstitialAdListener interstitialAdListener = new InterstitialAdListener() {
            @Override
            public void onInterstitialDisplayed(final Ad ad) {
                // Interstitial ad displayed callback
                Log.i(TAG, "Interstitial ad displayed.");
            }

            @Override
            public void onInterstitialDismissed(final Ad ad) {
                // Interstitial dismissed callback
                Log.i(TAG, "Interstitial ad dismissed.");
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
                Log.d(TAG, "Interstitial ad is loaded and ready to be displayed!");
                // switch loading signal to true
                isInterstitialLoaded = true;

            }
            @Override
            public void onAdClicked(final Ad ad) {
                // Ad clicked callback
                Log.i(TAG, "Interstitial ad clicked!");
            }
            @Override
            public void onLoggingImpression(final Ad ad) {
                // Ad impression logged callback
                Log.i(TAG, "Interstitial ad impression logged!");
            }
        };

        FbInterstitialAd.loadAd(
                FbInterstitialAd.buildLoadAdConfig()
                        .withAdListener(interstitialAdListener)
                        .build());
    }

    /**
     * Display a loaded Interstitial ad
     */
    public void ShowInterstitial(){
        if(isInterstitialLoaded){
            FbInterstitialAd.show();
            isInterstitialLoaded = false; //reset the signal to false so the Adloaded signal from the ad listener will set it to true again when ad is loaded
        }else{
            Log.e(TAG,"Interstitial is not Loaded yet !");
        }
    }

    /**
     * Load a Facebook rewarded video ad
     * @param placementId placement id
     */
    public void LoadRewardedVideo(String placementId){
        FbRewardedVideoAd = new RewardedVideoAd(activity,placementId);

        RewardedVideoAdListener rewardedVideoListener = new RewardedVideoAdListener() {
            @Override
            public void onRewardedVideoCompleted() {
                //TODO : Call Reward function ,
            }

            @Override
            public void onLoggingImpression(Ad ad) {

            }

            @Override
            public void onRewardedVideoClosed() {
                FbRewardedVideoAd.loadAd();
            }

            @Override
            public void onError(Ad ad, AdError adError) {
                Log.e(TAG, "Rewarded ad failed to load: " + adError.getErrorMessage());
            }

            @Override
            public void onAdLoaded(Ad ad) {
                isRewardedLoaded = true;
                Log.d(TAG, "Rewarded Video ad is loaded and ready to be displayed!");
            }

            @Override
            public void onAdClicked(Ad ad) {

            }
        };

        FbRewardedVideoAd.loadAd(
                FbRewardedVideoAd.buildLoadAdConfig()
                        .withAdListener(rewardedVideoListener)
                        .build());

    }

    /**
     * Display a loaded Rewarded Video Ad
     */
    public void ShowRewardedVideo(){
        if(isRewardedLoaded){
            isRewardedLoaded = false;
            FbRewardedVideoAd.show();
        }
    }


    /**
     *
     * @param placementId Banner Placement Id
     */
    public void LoadBanner(String placementId){

        AdView = new AdView(activity, placementId , AdSize.BANNER_HEIGHT_50);

        AdListener adListener = new AdListener() {
            @Override
            public void onError(Ad ad, AdError adError) {
                Log.e(TAG, "Banner Ad Failed : " + adError.getErrorMessage());
            }

            @Override
            public void onAdLoaded(Ad ad) {
                isBannerLoaded = true;
                Log.d(TAG, "Banner ad is loaded !");
            }

            @Override
            public void onAdClicked(Ad ad) {
                // Ad clicked callback
            }

            @Override
            public void onLoggingImpression(Ad ad) {
                // Ad impression logged callback
            }
        };

        Log.i(TAG,"Banner is loading...");

        AdView.loadAd(AdView.buildLoadAdConfig().withAdListener(adListener).build());
    }


    /**
     * Show Banner Ad
     */
    public void ShowBanner(){

        if(!isBannerLoaded){
            Log.e(TAG, "No Banner loaded to show : Call load_banner() first ");
            return;
        }

        if(isBannerShown){
            Log.e(TAG, "Banner already shown !");
            return;
        }

        AddBannerToLayout();
    }

    /**
     * hide Banner Ad
     */
    public void HideBanner(){

        if(!isBannerLoaded){
            Log.e(TAG, "No Banner loaded to hide : Call load_banner() first ");
            return;
        }

        if(!isBannerShown){
            Log.e(TAG, "Banner already Hidden !");
            return;
        }


        isBannerShown = false;
        isBannerLoaded = false;
        windowManager.removeView(linearLayout);
        linearLayout.removeView(AdView);
        linearLayout = null;
        AdView = null;

        Log.i(TAG, "Banner hidden !");
    }


    private void AddBannerToLayout(){

        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                linearLayout = new LinearLayout(activity);
                linearLayoutParams =  new LinearLayout.LayoutParams(
                        LinearLayout.LayoutParams.MATCH_PARENT,
                        LinearLayout.LayoutParams.MATCH_PARENT
                );
                linearLayoutParams.setMargins(0,0,0,0);


                windowManager = activity.getWindowManager();
                windowManagerParams = new WindowManager.LayoutParams();
                windowManagerParams.x = WindowManager.LayoutParams.MATCH_PARENT;
                windowManagerParams.y = WindowManager.LayoutParams.MATCH_PARENT;
                windowManagerParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
                windowManagerParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
                windowManagerParams.flags = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL
                        | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
                windowManagerParams.gravity = Gravity.BOTTOM;

                linearLayout.addView(AdView,linearLayoutParams);
                windowManager.addView(linearLayout,windowManagerParams);
                isBannerShown = true;
                Log.i(TAG, "Banner displaying !");
            }
        });

    }

}