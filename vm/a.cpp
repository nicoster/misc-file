/**   * General PAC file   *    * Some subtle differences from original Corp:    * * functions wwwDomIs and domainIs are missing. domainIs() functionallity built   * * into in_array() wildcard syntax. Both variants of wwwDomIs() targets must be   * * included into array - currently, only three.   * * fjc   **/    /**   * History   *   * v1.0 2-feb-2006 fjc epoch   * v1.2 3-Mar-2006 ap   * v1.3 8-Mar-2006 fjc: added Energy exception and array-based Subnets    *                      (multiple isInNet()calls are too expensive). Reused in_array()   *                      function with asterisk notation.   * v1.4 24-Apr-2006 fjc: added Energy net filter 3.66.*   * v1.5 1-jun-2006 fjc: added *.supplychainwebcenter.com to internal array   *			Also added Loopback adapter and non-routable IP nets   * v1.6 2-jun-2006 fjc: altered Jenbacher network mask to /21 (255.255.248.0) to   *			match their user vlan   *			Added EURO_PROXY variable for generic usage.   * v1.7 5-jun-2006 fjc: removed supplychainwebcenter.com from internal list   *			after finding out it's an Aviation only site   * v1.8 15-jun-2006 fjc: added Mexico proxy http-monterrey.fso.erie.ge.com   * v1.9 19-jun-2006 fjc: replaced http-proxy-bel.geips with http-proxy-frbel.geips.ge.com   * v1.10 2-aug-2006 fjc: added 172.25.* as a bypass address for UK   * v1.11 19-oct-2006 rns: added more proxy profiles.  added more energy subnets.  Mex Exceptions.   * v1.12 11-aug-2009 fjc: deployed for AE - note same proxy identified as backup   *                        no where to send so many clients: crush the wan, crush the remote proxies   *                        Adding Cardiff: sending them to Belfort since wccp will send them   *                          to the local machines, and PAC will only be used in failure mode.   *                        Adding Singapore: no vip   */    /*----------------------------------- Global Vars --------------------------------------------*/    /**    * Define proxy
 profiles  */
var _JENBACHER       = "PROXY geepgeatjenba01.geps.ge.com.:8080; PROXY httpproxy.geips.ge.com:8080";
var _RAIL_STD        = "PROXY http-proxy.trans.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _ENERGY_STD      = "PROXY http-proxy.geps.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _MINDEN_NV       = "PROXY nvminintpxy01a.psamer.ps.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _AE_STD          = "PROXY http-proxy.ae.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _DEV_PROXY       = "PROXY bc001dev.ae.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _RAIL_WARE_UK    = "PROXY http-proxy-frbel.geips.ge.com:80; PROXY http-proxy-euro.geps.ge.com:80";
var _EURO_PROXY      = "PROXY PROXY http-proxy-euro.geps.ge.com:80; http-proxy-frbel.geips.ge.com:80";
var _MEXICO_PROXY    = "PROXY http-monterrey.fso.erie.ge.com:80; PROXY http-proxy.ae.ge.com:80";
var _WILMINGTON_STD  = "PROXY bc001wilm.ae.ge.com:80; PROXY http-proxy.geps.ge.com:80";
var _CARDIFF_STD     = "PROXY powpgefrbelfo01.energy.ge.com:80; PROXY powpgefrbelfo02.energy.ge.com:80";
var _SINGAPORE_STD     = "PROXY POWpgSSGsinga01-DigiHub.tsg.ge.com:80; PROXY POWpgSSGsinga02-DigiHub.tsg.ge.com:80";       /**    * Assign proxy profile for this instance  */
var _proxy_path = _AE_STD;
var internalHosts    = new Array( );
var externalHosts    = new Array( );
var JenExceptions    = new Array( );
var energyExceptions = new Array( );
var energySubNets    = new Array( );
var MexExceptions    = new Array( );    /*----------------------------------- no proxy -----------------------------------------------*/
internalHosts.push( "*.ge.com" );
internalHosts.push( "3.*" );
internalHosts.push( "127.*" );
internalHosts.push( "172.25.*" );  //
internalHosts.push( "10.*" );  //
internalHosts.push( "192.168.*" );  //
internalHosts.push( "172.16.*" );
internalHosts.push( "129.201.*" );
internalHosts.push( "129.202.*" );
internalHosts.push( "web.penske.com" );
internalHosts.push( "insidenbc.com" );  //
internalHosts.push( "*.supplychainwebcenter.com" );  // Smiths
internalHosts.push( "*smiths.aero" );
internalHosts.push( "*ariba.smiths.com" );
internalHosts.push( "*mpcreports.smiths.com" );
internalHosts.push( "*mpc.smiths.com" );
internalHosts.push( "*legal-compliance.smiths.com" );
internalHosts.push( "*lc.smiths.com" );
internalHosts.push( "*intranet.smiths.com" );
internalHosts.push( "192.88.213.*" );
internalHosts.push( "*.vetco.com" );
internalHosts.push( "*.vetcogray.com" );    /*---------------------------------- proxy needed --------------------------------------------*/
externalHosts.push( "supersearch.ge.com" );
externalHosts.push( "ge.com" );
externalHosts.push( "www.ge.com" );
externalHosts.push( "benefits.ge.com" );
externalHosts.push( "www.benefits.ge.com" );
externalHosts.push( "*travel.ge.com" );
externalHosts.push( "*partsdirect.ge.com" );
externalHosts.push( "customerlink.ge.com" );
externalHosts.push( "www.customerlink.ge.com" );
externalHosts.push( "www.genstar.ge.com" );
externalHosts.push( "gess.ge.com" );
externalHosts.push( "pac.ge.com" );
externalHosts.push( "www.sfg.ge.com" );
externalHosts.push( "structuredproducts.ge.com" );
externalHosts.push( "commerce.supply.ge.com" );
externalHosts.push( "supplynet.ge.com" );
externalHosts.push( "payroll.ge.com" );
externalHosts.push( "ess.ge.com" );
externalHosts.push( "dropbox*.ge.com" );        /*------------------------- Jenbacher Exceptions ( no proxy ) --------------------------------*/
JenExceptions.push( "*.jenbacher.com" );
JenExceptions.push( "172.16.*" );
JenExceptions.push( "172.17.*" );
JenExceptions.push( "172.30.*" );
JenExceptions.push( "172.31.*" );
JenExceptions.push( "192.168.123.*" );
JenExceptions.push( "*.jenbach.jenbacher" );
JenExceptions.push( "hermes.jenbacher.com" );
JenExceptions.push( "my.firewall" );    /*------------------------- Mexico Exceptions ( no proxy ) --------------------------------*/    //
MexExceptions.push( "*portalcalidad" );  //
MexExceptions.push( "*portaljuridico" );  //
MexExceptions.push( "*portalsvx" );  //
MexExceptions.push( "*e-laboral" );  //
MexExceptions.push( "*xignuxps" );
/*------------------------- Energy Exceptions ( no proxy ) --------------------------------*/
energyExceptions.push( "*.inpo.org" );	// resolvable in Energy only      /*------------------------- Energy Subnetworks --------------------------------------------*/
energySubNets.push("3.10.*");
energySubNets.push("3.25.*");
energySubNets.push("3.29.*");
energySubNets.push("3.32.*");
energySubNets.push("3.43.*");
energySubNets.push("3.60.*");
energySubNets.push("3.66.*");
energySubNets.push("3.69.*");
energySubNets.push("3.72.*");
energySubNets.push("3.75.*");
energySubNets.push("3.76.*");
energySubNets.push("3.84.*");
energySubNets.push("3.96.*");
energySubNets.push("3.128.*");      /**   * main-function for Browser   * ( will be called by browser before a site will be accessed )   *   */
function FindProxyForURL( url, host )
{
    if ( isInternal( url, host ) )
    {
        return "DIRECT";
    }
    else
    {
        return _proxy_path;
    }
}    /**   * checking of a Jenbacher Client, if false --> check if host is matching internalHosts   *   * @author Andreas Pfister <andreas.pfister@ge.com>   *   * Adding additional business exception functions as else-if constructs (fjc)   *   */  function isInternal( url, host )
{
    if ( JenExc( host ) )
    {
        return true;
    }
    else if (energyExc(host) )
    {
        return true;
    }
    else
    {
        if ( !isExternal( url, host ) )
        {
            return ( in_array( host, internalHosts ) || isPlainHostName( host ) );
        }
        else
        {
            return false;
        }
    }
}
function isExternal( url, host )
{
    return in_array( host, externalHosts );
}      /**   * Searching for elements in an array and returning true if found, otherwise returning false   * if an asteriks will be found, function shExpMatch takes the matching   *   * @author Andreas Pfister <andreas.pfister@ge.com>   */ 
function in_array( nameOfElement, aElements )
{
    for ( var i in aElements )
    {
        if ( aElements[i].indexOf
                ("*") >= 0 )
        {
            if ( shExpMatch( nameOfElement.toLowerCase( ), aElements[i].toLowerCase( ) ) )
            {
                return true;
            }
        }
        else if ( aElements[i].toLowerCase( ) == nameOfElement.toLowerCase( ) )
        {
            return true;
        }
    }
    return false;
}    /**   * if ip-address of client in jenbacher ip-range, array JenExceptions is base for matching hosts   *   * @author Andreas Pfister <andreas.pfister@ge.com>   */  
function JenExc( host )
{  /**   *	3.69.248.0/21 is Jenbacher's User vlan  */    if ( isInNet( myIpAddress( ), "3.69.248.0", "255.255.248.0" ) )
    {
        if ( in_array( host, JenExceptions ) )
        {
            return true;
        }
    }
    return false;
}  /**   * if client's ip address is within Energy, look for no-proxy exceptions in energyExceptions array   *   */  
function energyExc(host)
{
    var client_addr = myIpAddress( );
    if ( in_array( client_addr, energySubNets ) )
    {
        if ( in_array( host, energyExceptions) )
        {
            return true;
        }
    }
    return false;
}
