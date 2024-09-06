# WARP
Warp is a lightweight and efficient task reminder system written in C, designed to help users stay on top of their important tasks. Warp can run silently in the background, ensuring that no task is forgotten, even if the main program is closed. With Warp, staying organized is effortless, allowing users to focus on their work without missing deadlines.

> **Disclaimer :**  
> Warp is meant to be used on a linux enviornment only.


## Table of Contents
- [Dependencies](https://github.com/himanshu-o5/warp?tab=readme-ov-file#dependencies)
- [Getting Started](https://github.com/himanshu-o5/warp?tab=readme-ov-file#getting-started)
- [Usage](https://github.com/himanshu-o5/warp?tab=readme-ov-file#usage)
- [Showcase](https://github.com/himanshu-o5/warp?tab=readme-ov-file#showcase)

## Dependencies

To build and run this project, you will need the following dependencies:

- **C Compiler**: Make sure you have `gcc`.
- **libnotify**: A library for sending desktop notifications. You can install it using your package manager:
  - **Debian/Ubuntu**: `sudo apt-get install libnotify-dev`
  - **Arch Linux**: `sudo pacman -S libnotify`
- **System Utilities**: Ensure that `notify-send` is available on your system for sending notifications.

Make sure you have these dependencies installed before building the project.


## Getting Started
1. Start by cloning this repository to your local machine : 

    ```bash
    git clone https://github.com/himanshu-o5/warp.git
    ```

2. Navigate to the project directory.

    ```bash
    cd warp/
    ```

3. Run the compile.sh script to compile for your machine.
    ```bash
    ./compile.sh
    ```

## Usage
### Warp GUI : `./warp`
- **Adding Reminders :** Reminders can be added by providing a future date-time and a note for the reminder.
- **Listing Reminders :** You can see your added reminders by listing them.


### Daemon Warp

- **./warp init :** For running the demon process, execute `./warp init` which will keep checking for any due reminder. Furthermore, you can add this to your startup files, so that it will start when you boot into your machine.

- **./warp halt :** To stop the daemon process. 

## Showcase
![Homepage](https://github.com/himanshu-o5/warp/blob/master/assets/warp_homepage.png?raw=true)

![Add Reminder](https://github.com/himanshu-o5/warp/blob/master/assets/warp_addReminder.png?raw=true)

![Notify](https://github.com/himanshu-o5/warp/blob/master/assets/notify_warp.png?raw=true)

![List Reminders](https://github.com/himanshu-o5/warp/blob/master/assets/warp_listReminders.png?raw=true)
