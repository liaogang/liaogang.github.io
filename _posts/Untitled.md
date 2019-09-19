iOS 让指定的后台app不被watchdog杀死

https://github.com/ashikase/Backgrounder
 BackBoardServices.framework
 AssertionServices.framework 
 
BKSProcessAssertion http://iphonedevwiki.net/index.php/BKSProcessAssertion

cydia tweak, watchdog lite



Setting up public key authentication

Key based authentication in SSH is called public key authentication. The purpose of ssh-copy-id is to make setting up public key authentication easier. The process is as follows.
Generate an SSH Key

With OpenSSH, an SSH key is created using ssh-keygen. In the simplest form, just run ssh-keygen and answer the questions. The following example illustates this.

Creating a key pair (public key and private key) only takes a minute. The key files are usually stored in the ~/.ssh directory.
Copy the key to a server

Once an SSH key has been created, the ssh-copy-id command can be used to install it as an authorized key on the server. Once the key has been authorized for SSH, it grants access to the server without a password.

ssh-copy-id -p 2222 root@lh


How to disable strict host key checking in ssh?


In your ~/.ssh/config (if this file doesn't exist, just create it):

Host *
    StrictHostKeyChecking no
This will turn it off for all hosts you connect to. You can replace the * with a hostname pattern if you only want it to apply to some hosts.  

Make sure the permissions on the file restrict access to yourself only:

sudo chmod 400 ~/.ssh/config





