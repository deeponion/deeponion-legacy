![alt text](https://image.ibb.co/mfR4R6/DO.png "DeepOnion")
=====================================

##### This is DeepOnion legacy source code. It is superseded by the new code based on the latest bitcoin/litecoin codebase. All DeepOnion features are ported to the new codebase. The legacy codebase will be frozen unless for the critical bug fixes. It will co-exist with the new wallet for a while, then we will stop using the legacy codebase (timeline to be determined).

#### Starting from December 10, 2019, the legacy code will no longer be supported by the DeepOnion dev team.

DeepOnion (ONION) is an anonymous and untraceable cryptocurrency. All transactions are private and sent through the TOR network.

The integration with TOR ensures that users are always on a secure environment. There is no client-side configuration needed. Our client will automatically join the TOR network and connect to available TOR nodes on the network (including our seed nodes). After a successful connection to the DeepOnion network, you may check your displayed IP using the DeepOnion client console, where you will see that your client is assigned a TOR hidden service address (.onion address).

#### Pluggable Transports

>DeepOnion has expanded and added the option for advanced users to configure PTs such as obfs4 & Meek. 
>
>Instructions:
>
>[Setup obfs4]( https://github.com/deeponion/deeponion/blob/master/doc/setup-obfs4.md)
>
>[Setup Meek]( https://github.com/deeponion/deeponion/blob/master/doc/setup-meek.md)


## Specifications

| Specification | Value |
|:-----------|:-----------|
| Consensus Algorithm | `PoW & PoS` |
| Mining Algorithm | `X13` |
| Confirmations | `5 tx` |
| Block Confirm. | `50 minted confirms` |
| Port | `17570` |
| RPC Port | `18580` |


##### PoW:

> - 240 sec block interval.
> - Difficulty readjustment every block.
> - Initial block reward will be 8 ONIONs per block.
> - PoW block reward will be halved every year, until it reaches 1 ONION/block where it will remain.

##### PoS:

> - 60 sec block interval.
> - Difficulty readjustment every block.
> - PoS interest will be variable per year:
> 	1st year: `10%`
> 	2nd year: `5%`
> 	3rd and subsequent years: `1%`
> - Minimum holding time before the PoS will be generated is 1 day.
> - Maximum allowed accumulated coin is 30 days.


## Resources

:package: For software downloads, please see [Downloads](https://deeponion.org/#downloads)

[Whitepaper](https://deeponion.org/White-Paper.pdf) 

[Roadmap](https://deeponion.org/#roadmap)

[AirDrop](https://deeponion.org/airdrop.html)

[Community](https://deeponion.org/community/)

[Support](https://deeponion.help)


## DeepOnion.conf file

Download [DeepOnion.conf](https://deeponion.org/DeepOnion.conf.php?action=download) (right-click > save link as).

For more info on how setup your .conf file, please visit https://deeponion.org/DeepOnion.conf.php

License :bookmark_tabs:
-------

DeepOnion is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.



Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be completely stable. 


