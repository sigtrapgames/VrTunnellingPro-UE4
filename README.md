VR Tunnelling Pro (VRTP) is the most advanced VR comfort solution for Unreal Engine 4.20+. It can be dropped in to almost any project for plug-and-play comfort options. It's developed by Sigtrap with support from Oculus, and currently supports Oculus Rift.

*VRTP is currently in beta for UE4.*

VRTP is designed not only as a plugin, but a platform for experimenting with and developing new comfort techniques. Familiarity with the source will allow developers to quickly implement new techniques.

## Quick Installation & Usage
To use the plugin within your project:
* Go to [Releases](https://github.com/sigtrapgames/VrTunnellingPro-UE4/Releases) to download the plugin for your Unreal Engine version
* Copy the plugin folder either to your project's /plugins folder
* Alternatively, the plugin can be used as an engine plugin, by copying the folder into your engine version, under the plugins/marketplace folder
* When you open UE4, either hit the Manage Plugins button that pops up, or select the Edit -> Plugins menu item
* Locate the plugin in the list and Enable it. Unreal will request a restart in order to enable the plugin
* Drop a VRTP component onto your player character blueprint. Note that this blueprint must have a camera attached in order to activate the plugin effect

## What is Tunnelling?
Much of VRTP's core is based on "Tunnelling", a technique to reduce sim-sickness in VR games, experiences and apps.

Artificial locomotion in VR - cars, spaceships, first-person "thumbstick" movement - causes sim-sickness in many users. This is a result of a mismatch between the motion they feel and the motion they see. Tunnelling is a highly effective method to reduce this for a large number of users.

It works by fading out peripheral vision. The subconscious uses peripheral vision heavily to interpret motion but the conscious brain largely ignores it - as such, reducing motion in the periphery combats the overall motion disparity users feel without significant information loss.

Additionally, the periphery can be replaced with static imagery - such as a skybox - to counteract motion even more strongly, "grounding" users in a static reference frame.

![VR Tunnelling Pro](https://thumbs.gfycat.com/DemandingDecentChicken-size_restricted.gif)

## Key Features
* Scene Component that can be dropped onto your player character
  * Automatically locates the player camera and builds the effect
  * Additional components included for easy masking (see below)
* Multiple modes
  * Color vignette
  * Replace periphery with skybox/cubemap
  * View VR scene through static "windows"
  * View skybox / color through world-space portals
  * Blur vignette with optional color
* Masking
  * Exclude objects from the tunnelling effect
    * e.g. static cockpit to help ground users
    * Simply drop a VRTP Mask component onto any static mesh to apply the masking to it
* Fully configurable
  * Tweak any settings in-editor or at runtime for full control
  * Preset system
    * Easily define multiple presets that users can switch between at runtime
    * Create your own presets using the built-in VRTP Preset Data Asset type
    * Switch between your preset and previously applied settings, non-destructively
* Mobile-friendly version coming soon

## Roadmap
We are working on multiple new techniques which are being developed on the *dev* branch. These include 3D cages, artificial tilt and more.

We will be looking to support all major VR platforms including
* Oculus Go and Quest
* HTC Vive
* Playstation VR
* Samsung GearVR
* Google Daydream

A Mobile-friendly version is in the works and will be ready shortly. This version will be highly optimised for mobile and will not employ post process settings or HDR, providing the highest level of device compatibility.

Full documentation will be made available at [http://www.sigtrapgames.com](http://www.sigtrapgames.com). Check out our talk [Integrating Locomotion in Unity, Unreal, and Native Engines](https://www.youtube.com/watch?v=dBs65za8fhM) from Oculus Connect 5.

## Credits
Developed and maintained by Darby Costello ([@darbycostello](https://twitter.com/darbycostello) | [github](https://github.com/darbycostello))  
Ported from [Unity version](https://github.com/sigtrapgames/VrTunnellingPro-Unity) originally developed by Dr Luke Thompson ([@six_ways](https://twitter.com/six_ways) | [github](https://github.com/SixWays))   
Research and support by Tom Heath on behalf of Oculus  
Art assets by Gary Lloyd ([@garylloyd89](https://twitter.com/garylloyd89))
