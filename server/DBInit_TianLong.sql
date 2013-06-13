/*==============================================================*/
/* Database name:  tlbbdb                                       */
/* DBMS name:      MySQL 3.23                                   */
/* Created on:     2007-7-20 15:07:53                           */
/*==============================================================*/

create database if not exists tlbbdb;
use tlbbdb;

drop index Index_ab_charguid on t_ability;

drop index Index_char_accname on t_char;

drop index Index_char_charguid on t_char;

drop index Index_char_charname on t_char;

drop index Index_city_poolid on t_city;

drop index Index_crc_charguid on t_crc32;

drop index Index_cshop_PoolId on t_cshop;

drop index Index_cshopitem_cshopid on t_cshopitem;

drop index Index_guild_gguild on t_guild;

drop index Index_impact_charguid on t_impact;

drop index Index_it_charguid on t_iteminfo;

drop index Index_it_itemguid on t_iteminfo;

drop index Index_itk_sid on t_itemkey;

drop index Index_mail_mail on t_mail;

drop index Index_mi_charguid on t_mission;

drop index Index_Pet_Charguid on t_pet;

drop index Index_pcre_pindex on t_petcreate;

drop index Index_pshop_shopguid on t_pshop;

drop index Index_pshop_sidpid on t_pshop;

drop index Index_re_charguid on t_relation;

drop index Index_sk_charguid on t_skill;

drop index Index_xinfa_charguid on t_xinfa;

drop table if exists t_ability;

drop table if exists t_char;

drop table if exists t_charextra;

drop table if exists t_city;

drop table if exists t_crc32;

drop table if exists t_cshop;

drop table if exists t_cshopitem;

drop table if exists t_global;

drop table if exists t_guild;

drop table if exists t_impact;

drop table if exists t_iteminfo;

drop table if exists t_itemkey;

drop table if exists t_mail;

drop table if exists t_mission;

drop table if exists t_pet;

drop table if exists t_petcreate;

drop table if exists t_pshop;

drop table if exists t_relation;

drop table if exists t_skill;

drop table if exists t_var;

drop table if exists t_xfallexp;

drop table if exists t_xinfa;

/*==============================================================*/
/* Database: tlbbdb                                             */
/*==============================================================*/
create database if not exists tlbbdb;

use tlbbdb;

/*==============================================================*/
/* Table: t_ability    生活技能                                         */
/*==============================================================*/
create table if not exists t_ability
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   abid                           smallint                       not null,
   ablvl                          smallint                       not null,
   abexp                          int unsigned                   not null,
   dbversion                      int                            default 0,
   isvalid                        int                            default 1,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_ab_charguid                                     */
/*==============================================================*/
create index Index_ab_charguid on t_ability
(
   charguid
);

/*==============================================================*/
/* Table: t_char   角色表  　                                   */
/*==============================================================*/
create table if not exists t_char
(
   aid                            bigint                         not null AUTO_INCREMENT ,
   accname                        varchar(50) binary             not null,
   charguid                       int                            not null,
   charname                       varchar(50) binary             not null,
   title                          varchar(50)                    not null,
   pw                             varchar(15)                    not null,
   sex                            smallint                       not null,
   level                          int                            not null,
   enegry                         int                            not null,
   outlook                        int                            not null,
   scene                          int                            not null,
   xpos                           int                            not null,
   zpos                           int                            not null,
   menpai                         smallint                       not null,
   hp                             int                            not null,
   mp                             int                            not null,
   strikepoint                    smallint                       not null,
   camp                           varchar(50) binary             not null,
   str                            int                            not null,
   con                            int                            not null,
   dex                            int                            not null,
   spr                            int                            not null,
   ipr                            int                            not null,
   points                         int                            not null,
   logouttime                     int                            not null,
   logintime                      int                            not null,
   createtime                     int                            not null,
   dbversion                      int                            not null default 0,
   haircolor                      int                            not null,
   hairmodel                      int                            not null,
   facecolor                      int                            not null,
   facemodel                      int                            not null,
   vmoney                         int                            not null,
   isvalid                        smallint                       not null,
   exp                            int                            not null,
   pres                           text                           not null,
   mdata                          text,
   mflag                          text,
   relflag                        text,
   settings                       text                             not null,
   shopinfo                       text,
   carrypet                       varchar(20)                    not null,
   guldid                         int                            not null,
   teamid                         int                            not null,
   headid                         int                            not null,
   erecover                       int                            not null,
   RMB                            int                            not null default 0,
   vigor                          int                            not null,
   maxvigor                       int                            not null,        
   BankRMB                        int                            not null default 0,
   vrecover                       int                            not null,
   energymax                      int                            not null,
   pwdeltime                      int                            not null,
   pinfo                          text,
   bkscene                        int,
   bkxpos                         int,
   bkzpos                         int,
   titleinfo                      text,
   dietime                        int                            not null,
   bankmoney                      int                            not null,
   bankend                        int                            not null,
   cooldown                       text,
   rage                           int                            default 0,
/* reserve                        varchar(100),*/
/* dinfo                          int                            default 0,*/
/* defeq                          int                            default -1,*/
/* guildpoint                     int                            default 0,*/
/* menpaipoint                    int                            default 0,*/
/* gevil                          int                            default 0,*/
/* pkvalue                        int                            default 0,*/
/* otime                          int                            default 0,*/
/* deltime                        int                            default 0,*/
/* expinfo                        varchar(200)                   default '0',*/
/* savetime                       int                            default 0,*/
/* crc32                          int                            default 0,*/
/* pvpinfo                        text                           default NULL,*/
/* loginip                        int                            not null default 0,*/
/* pkvaluetime                    int                            not null default 0,*/
/* fatigue                        varchar(40)                    default NULL,*/
/* yuanbao                        int                            not null default 0,*/
/* visualgem                      text                           default NULL,*/
/* isolditem                      smallint                       not null default 0,*/
/* uipoint                        int                            not null default 0,*/
/* zengdian                       int                            not null default 0,*/
   primary key (aid, charname)
);

delimiter //
drop procedure delete_char_new//
create procedure delete_char_new(
pcharname             varchar(100),
paccount              varchar(100),
pcharguid             int,
pdeltime              int,
pcrc32                int)
begin
declare rcharguid   int;
declare rlevel      int;
declare rdeltime    int;
declare rnext       int;
declare rdbversion  int;
declare rcrc        int;
set     rcharguid = -1;
set     rnext = 0;
set     rdbversion = 0;
start transaction;
select charguid,level,deltime,crc32 into rcharguid,rlevel,rdeltime,rcrc from t_char
    where accname=paccount and charguid = pcharguid and isvalid=1;
if rcharguid<>-1 then
    if rlevel<1 then
          update t_char set isvalid = 0,charname = CONCAT(charname,'@DELETE_',pcharguid)
            where accname= paccount and charguid = pcharguid;
          select dbversion into rdbversion from t_char
            where accname= paccount and charguid = pcharguid;
          set rnext = 1;
    else 
       set rcrc = rcrc + pcrc32;
       if rdeltime=0 then
            update t_char set deltime= pdeltime,crc32=rcrc where charguid= pcharguid;        
       end if;
    end if;
end if;
commit;
    select rnext,rdbversion;
end;//
delimiter ;

delimiter //
drop procedure fetch_savetime//
create procedure fetch_savetime(
pcharguid    int
)
begin
    declare     visvalidtime              int;
    declare     vsavetime             int;
    declare     vnowtime              int;
    declare     vupdatetime          int;
    set         vsavetime = -1;
    set         vnowtime  = -1;
    set         visvalidtime = 0;
     start transaction;
     select savetime into vsavetime from t_char where charguid = pcharguid;
     if vsavetime = -1 then
        set  visvalidtime = 1;
     else
          set vnowtime = time_to_sec(now());
           if    abs(vsavetime-vnowtime)<300 then
              set  visvalidtime = 2;
          else
            
               update t_char set savetime = vnowtime where charguid = pcharguid;
               select savetime into vupdatetime from t_char where charguid = pcharguid;
               if vupdatetime = vnowtime then
                   set visvalidtime = 3;
               else
                    set visvalidtime = 4;
               end if;
           end if;
     end if;
  commit;
    select visvalidtime;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_char_charguid                                   */
/*==============================================================*/
create unique index Index_char_charguid on t_char
(
   charguid
);

/*==============================================================*/
/* Index: Index_char_accname                                    */
/*==============================================================*/
create index Index_char_accname on t_char
(
   accname
);

/*==============================================================*/
/* Index: Index_char_charname                                   */
/*==============================================================*/
create unique index Index_char_charname on t_char
(
   charname
);

/*==============================================================*/
/* Table: t_charextra                                           */
/*==============================================================*/
create table if not exists t_charextra
(
   charguid                       int                            not null,
   dbversion                      int                            not null default 0,
   buyyuanbao                     int                            not null default 0,
   kmcount                        int                            not null default 0,
   cmcount                        tinyint                        not null default 0,
   primary key (charguid)
);

delimiter //
drop procedure save_charextra//
create procedure save_charextra(
pcharguid           int,
pdbversion          int,
pbuyyuanbao         int,
pkmcount            int,
pcmcount            tinyint
)
begin
    declare sameid  int;
    set sameid = -1;
    
    select charguid into sameid from t_charextra where charguid=pcharguid;
    if  sameid <> -1 then
        update t_charextra set dbversion=pdbversion,buyyuanbao=pbuyyuanbao,kmcount=pkmcount,cmcount=pcmcount
        where charguid=pcharguid;
    else
        insert into t_charextra (charguid,dbversion,buyyuanbao,kmcount,cmcount)
        values (pcharguid,pdbversion,pbuyyuanbao,pkmcount,pcmcount);
    end if;
end;//
delimiter ;


/*==============================================================*/
/* Table: t_city                                                */
/*==============================================================*/
create table if not exists t_city
(
   aid                            bigint                         not null AUTO_INCREMENT ,
   poolid                         int                            not null,
   citydata                       longtext                       not null,
   isvalid                        int                            not null,
   primary key (aid)
);

delimiter //
drop procedure save_cityinfo//
create procedure save_cityinfo(pcitydata longtext,ppoolid int,pisvalid int)
begin
declare rcount int;
start transaction;
select poolid into rcount from t_city where poolid = ppoolid;
if rcount = ppoolid then
        update t_city set citydata=pcitydata,isvalid=pisvalid
                where poolid=ppoolid;
else
        insert into t_city(poolid,citydata,
            isvalid)  values(ppoolid,pcitydata,pisvalid);    
end if;
commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_city_poolid                                     */
/*==============================================================*/
create index Index_city_poolid on t_city
(
   poolid
);

/*==============================================================*/
/* Table: t_crc32                                               */
/*==============================================================*/
create table if not exists t_crc32
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   logouttime                     int                            not null,
   crc32                          int                            not null,
   fulldata                       longtext                       not null,
   isdelete                       smallint                       not null default 0,
   server                         int                            not null,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_crc_charguid                                    */
/*==============================================================*/
create index Index_crc_charguid on t_crc32
(
   charguid
);

/*==============================================================*/
/* Table: t_cshop                                               */
/*==============================================================*/
create table if not exists t_cshop
(
   aid                            bigint                         not null AUTO_INCREMENT,
   worldid                        int                            not null,
   serverid                       int                            not null,
   poolid                         int                            not null,
   isvalid                        int                            not null default 0,
   cshopid                        int                            not null default -1,
   primary key (aid)
);

delimiter //
drop procedure save_cshop//
create procedure save_cshop(
pworldid            int,
pserverid           int,
ppoolid             int,
pcshopid            int
)
begin
    declare sameid  int;
    set sameid = -1;
    
start transaction;
    select poolid into sameid from t_cshop 
    where worldid=pworldid and serverid=pserverid and poolid=ppoolid;
    if  sameid <> -1 then
        update t_cshop set cshopid=pcshopid,isvalid=1
        where worldid=pworldid and serverid=pserverid and poolid=ppoolid;
    else
        insert into t_cshop (worldid,serverid,poolid,isvalid,cshopid)
        values (pworldid,pserverid,ppoolid, 1, pcshopid);
    end if;
commit;

end;//
delimiter ;


/*==============================================================*/
/* Index: Index_cshop_PoolId                                    */
/*==============================================================*/
create unique index Index_cshop_PoolId on t_cshop
(
   worldid,
   serverid,
   poolid
);

/*==============================================================*/
/* Table: t_cshopitem                                           */
/*==============================================================*/
create table if not exists t_cshopitem
(
   aid                            bigint                         not null AUTO_INCREMENT,
   cshopid                        int                            not null,
   cshoppos                       int                            not null,
   serial                         int                            not null default 0,
   charguid                       int                            not null,
   charname                       varchar(50) binary             not null,
   gtype                          smallint                       not null,
   gvalue                         int                            not null default 0,
   svalue                         int                            not null default 0,
   ctime                          int                            not null default 0,
   costctime                      int                            not null default 0,
   isvalid                        int                            not null default 0,
   primary key (aid)
);

delimiter //
drop procedure save_cshopitem//
create procedure save_cshopitem(
pcshopid            int,
pcshoppos           int,
pserial             int,
pcharguid           int,
pcharname           varchar(50) binary,
pgtype              smallint,
pgvalue             int,
psvalue             int,
pctime              int,
pcostctime          int
)
begin
    declare sameid  int;
    declare samepos int;
    set sameid = -1;
    set samepos = -1;

start transaction;
    select cshopid,cshoppos into sameid,samepos 
    from t_cshopitem 
    where cshopid=pcshopid and cshoppos=pcshoppos;
    
    if  sameid <> -1 then
        update t_cshopitem
        set serial=pserial,charguid=pcharguid,charname=pcharname,
            gtype=pgtype,gvalue=pgvalue,svalue=psvalue,ctime=pctime,
            costctime=pcostctime,isvalid=1
        where cshopid=pcshopid and cshoppos=pcshoppos;
    else
        insert into t_cshopitem (cshopid,cshoppos,serial,charguid,charname,gtype,gvalue,svalue,ctime,costctime,isvalid) 
        values (pcshopid,pcshoppos,pserial,pcharguid,pcharname,pgtype,pgvalue,psvalue,pctime,pcostctime,1);
    end if;
commit;

end;//
delimiter ;


/*==============================================================*/
/* Index: Index_cshopitem_cshopid                               */
/*==============================================================*/
create unique index Index_cshopitem_cshopid on t_cshopitem
(
   cshopid,
   cshoppos
);

/*==============================================================*/
/* Table: t_global                                              */
/*==============================================================*/
create table if not exists t_global
(
   poolid                         int                            not null,
   data1                          int                            not null,
   primary key (poolid)
);

delimiter //
drop procedure save_global//
create procedure save_global(
ppoolid             int,
pdata1              int
)
begin
    declare sameid  int;
    set sameid = -1;
    
    select poolid into sameid from t_global where poolid=ppoolid;
    if  sameid <> -1 then
        update t_global set data1=pdata1 where poolid=ppoolid;
    else
        insert into t_global (poolid,data1) values (ppoolid, pdata1);
    end if;
end;//
delimiter ;


/*==============================================================*/
/* Table: t_guild                                               */
/*==============================================================*/
create table if not exists t_guild
(
   aid                            bigint                         not null AUTO_INCREMENT,
   guildid                        int                            not null,
   guildname                      varchar(50)                    not null,
   guildstat                      int                            not null,
   chiefguid                      int                            not null,
   pcount                         int                            not null,
   ucount                         int                            not null,
   mucount                        int                            not null,
   gpoint                         int                            not null,
   guildmoney                     int                            not null,
   cityid                         int                            not null,
   time                         int                            not null,
   logevity                       int                            not null,
   contribu                       int                            not null,
   honor                          int                            not null,
   indlvl                         int                            not null,
   agrlvl                         int                            not null,
   comlvl                         int                            not null,
   deflvl                         int                            not null,
   techlvl                        int                            not null,
   ambilvl                        int                            not null,
   admin                          text                           not null,
   guilddesc                      varchar(150)                   not null,
   chiefname                      varchar(50)                    not null,
   cname                          varchar(50)                    not null,
   glvl                           int                            not null,
   isvalid                        int                            not null,
   guilduser                      text                           not null,
   guildmsg                       varchar(300)                   not null,
   guildextra                     text                           not null,
   primary key (aid)
);

delimiter //
drop procedure save_guildinfo//
create procedure save_guildinfo(
pguildid              int          ,
pguildname            varchar(50)  ,
pguildstat            int          ,
pchiefguid            int          ,
ppcount               int          ,
pucount               int          ,
pmucount              int          ,
pgpoint               int          ,
pguildmoney           int          ,
pcityid               int          ,
ptime                 int          ,
plogevity             int          ,
pcontribu             int          ,
phonor                int          ,
pindlvl               int          ,
pagrlvl               int          ,
pcomlvl               int          ,
pdeflvl               int          ,
ptechlvl              int          ,
pambilvl              int          ,
padmin                text                  ,
pguilddesc            varchar(150) ,
pchiefname            varchar(50)  ,
pcname                varchar(50)  ,
pglvl                 int         ,
pguilduser            text        ,
pisvalid              int,
pguildmsg             varchar(300))
begin

declare rcount int;

start transaction;
select guildid into rcount from t_guild where guildid = pguildid;
if rcount = pguildid then
            update t_guild set guildid          =pguildid,   
          guildname        =pguildname ,
          guildstat        =pguildstat ,
          chiefguid        =pchiefguid ,
          pcount           =ppcount,    
          ucount           =pucount,    
          mucount          =pmucount,   
          gpoint           =pgpoint,    
          guildmoney       =pguildmoney,
          cityid           =pcityid,    
          time             =ptime,      
          logevity         =plogevity,  
          contribu         =pcontribu,  
          honor            =phonor,     
          indlvl           =pindlvl,    
          agrlvl           =pagrlvl,    
          comlvl           =pcomlvl,    
          deflvl           =pdeflvl,    
          techlvl          =ptechlvl,   
          ambilvl          =pambilvl,   
          admin            =padmin,     
          guilddesc        =pguilddesc, 
          chiefname        =pchiefname, 
          cname            =pcname,     
          glvl             =pglvl,      
          guilduser        =pguilduser,
          isvalid          =pisvalid,
          guildmsg         =pguildmsg 
          where guildid       =pguildid;
else
    insert into t_guild(guildid,
                            guildname,   
                            guildstat,   
                            chiefguid,   
                            pcount,      
                            ucount,      
                            mucount,     
                            gpoint,      
                            guildmoney,  
                            cityid,      
                            time,        
                            logevity,    
                            contribu,    
                            honor,       
                            indlvl,      
                            agrlvl,      
                            comlvl,      
                            deflvl,      
                            techlvl,     
                            ambilvl,     
                            admin,       
                            guilddesc,   
                            chiefname,   
                            cname,       
                            glvl,        
                            guilduser,
                            isvalid,
                            guildmsg)    values
                            (pguildid,
                             pguildname, 
                             pguildstat, 
                             pchiefguid, 
                             ppcount,   
                             pucount,   
                             pmucount,  
                             pgpoint,   
                             pguildmoney,
                             pcityid,   
                             ptime,     
                             plogevity, 
                             pcontribu, 
                             phonor,    
                             pindlvl,   
                             pagrlvl,   
                             pcomlvl,   
                             pdeflvl,   
                             ptechlvl,  
                             pambilvl,  
                             padmin,    
                             pguilddesc,
                             pchiefname,
                             pcname,    
                             pglvl,     
                             pguilduser,
                             pisvalid,
                             pguildmsg) ;
end if;

commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_guild_gguild                                    */
/*==============================================================*/
create unique index Index_guild_gguild on t_guild
(
   guildid
);

/*==============================================================*/
/* Table: t_impact                                              */
/*==============================================================*/
create table if not exists t_impact
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   imdata                         text                           not null,
   dbversion                      int                            default 0,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_impact_charguid                                 */
/*==============================================================*/
create index Index_impact_charguid on t_impact
(
   charguid
);

/*==============================================================*/
/* Table: t_iteminfo    装备表                                  */
/*==============================================================*/
create table if not exists t_iteminfo
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   guid                           int                            not null,
   world                          int                            not null,
   server                         int                            not null,
   itemtype                       int                            not null,
   pos                            smallint                       not null,
   p1                             int                            not null,
   p2                             int                            not null,
   p3                             int                            not null,
   p4                             int                            not null,
   p5                             int                            not null,
   p6                             int                            not null,
   p7                             int                            not null,
   p8                             int                            not null,
   p9                             int                            not null,
   p10                            int                            not null,
   p11                            int                            not null,
   p12                            int                            not null,
   p13                            int                            not null,
   p14                            int                            not null,
   p15                            int                            default 0,
   p16                            int                            default 0,
   p17                            int                            default 0,   
   creator                        varchar(40)                    default '0',
   isvalid                        smallint                       not null default 1,
   dbversion                      int                            default 0,
   fixattr                        varchar(200)                   not null,
   var                            varchar(40)                    default '0',
   visualid                       int                            not null default 0,
   maxgemid                       int                            not null default -1,
   primary key (aid)
);

delimiter //
drop procedure save_iteminfo//
create procedure save_iteminfo(
pcharguid             int,
pguid                 int,
pworld                int,
pserver               int,
pitemtype             int,
ppos                  smallint,
pvisualid             int,
pmaxgemid             int,
pfixattr              varchar(100),
pp1                   int,
pp2                   int,
pp3                   int,
pp4                   int,
pp5                   int,
pp6                   int,
pp7                   int,
pp8                   int,
pp9                   int,
pp10                  int,
pp11                  int,
pp12                  int,
pp13                  int,
pp14                  int,
pp15                  int,
pp16                  int,
pp17                  int,
pisvalid              smallint,
pdbversion            int,
pcreator              varchar(40),
pvar                  varchar(40))
begin

declare rguid      int;
declare rpos       int;
declare rdbversion int;
declare sameid     int;
set     sameid     =   -1;

start transaction;
select guid into sameid from t_iteminfo
    where world=pworld and server=pserver and guid=pguid and isvalid=1;

if sameid<>-1 then
    update t_iteminfo set isvalid =0 where world=pworld and server=pserver and guid=pguid;
end if;

select charguid,pos,dbversion into rguid,rpos,rdbversion from t_iteminfo
    where charguid = pcharguid and pos=ppos limit 1;
    if rguid = pcharguid then
     update t_iteminfo set charguid = pcharguid,
        guid             = pguid,
        world             = pworld,
        server             = pserver,
        itemtype         = pitemtype,
        pos            = ppos,
        visualid        = pvisualid,
        maxgemid        = pmaxgemid,
        fixattr             = pfixattr,
        p1            = pp1,
        p2            = pp2,
        p3            = pp3,
        p4            = pp4,
        p5            = pp5,
        p6            = pp6,
        p7            = pp7,
        p8            = pp8,
        p9            = pp9,
        p10            = pp10,
        p11            = pp11,
        p12            = pp12,
        p13            = pp13,
        p14            = pp14,
        p15            = pp15,
        p16            = pp16,
        p17            = pp17,
        isvalid          = pisvalid,
        dbversion        = pdbversion,
        creator          = pcreator,
        var            = pvar where
        charguid=pcharguid and pos=ppos and rdbversion<=pdbversion;

    else
        insert into t_iteminfo(charguid,world,server,guid,itemtype,
        pos,visualid,maxgemid,fixattr,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,
        isvalid,dbversion,creator,var)
        values(pcharguid,pworld,pserver,pguid,pitemtype,ppos,pvisualid,pmaxgemid,
        pfixattr,pp1,pp2,pp3,pp4,pp5,pp6,pp7,pp8,pp9,pp10,
        pp11,pp12,pp13,pp14,pp15,pp16,pp17,pisvalid,pdbversion,pcreator,pvar);
    end if;
commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_it_charguid                                     */
/*==============================================================*/
create index Index_it_charguid on t_iteminfo
(
   charguid
);

/*==============================================================*/
/* Index: Index_it_itemguid                                     */
/*==============================================================*/
create index Index_it_itemguid on t_iteminfo
(
   guid,
   world,
   server
);

/*==============================================================*/
/* Table: t_itemkey                                             */
/*==============================================================*/
create table if not exists t_itemkey
(
   aid                            bigint                         not null AUTO_INCREMENT,
   sid                            int                            not null,
   smkey                          int                            not null,
   serial                         int                            not null,
   primary key (aid)
);

insert into t_itemkey(sid,smkey,serial) values(0,7001,1001);
insert into t_itemkey(sid,smkey,serial) values(1,7002,1001);
insert into t_itemkey(sid,smkey,serial) values(2,7003,1001);
insert into t_itemkey(sid,smkey,serial) values(3,7004,1001);
insert into t_itemkey(sid,smkey,serial) values(4,7005,1001);
insert into t_itemkey(sid,smkey,serial) values(5,7006,1001);
insert into t_itemkey(sid,smkey,serial) values(6,7007,1001);
insert into t_itemkey(sid,smkey,serial) values(7,7008,1001);
insert into t_itemkey(sid,smkey,serial) values(8,7009,1001);
insert into t_itemkey(sid,smkey,serial) values(9,7010,1001);
insert into t_itemkey(sid,smkey,serial) values(10,7011,1001);
insert into t_itemkey(sid,smkey,serial) values(11,7012,1001);
insert into t_itemkey(sid,smkey,serial) values(12,7013,1001);
insert into t_itemkey(sid,smkey,serial) values(13,7014,1001);
insert into t_itemkey(sid,smkey,serial) values(14,7015,1001);
insert into t_itemkey(sid,smkey,serial) values(15,7016,1001);
insert into t_itemkey(sid,smkey,serial) values(16,7017,1001);
insert into t_itemkey(sid,smkey,serial) values(17,7018,1001);
insert into t_itemkey(sid,smkey,serial) values(18,7019,1001);
insert into t_itemkey(sid,smkey,serial) values(19,7020,1001);
insert into t_itemkey(sid,smkey,serial) values(20,7021,1001);
insert into t_itemkey(sid,smkey,serial) values(21,7022,1001);
insert into t_itemkey(sid,smkey,serial) values(22,7023,1001);
insert into t_itemkey(sid,smkey,serial) values(23,7024,1001);
insert into t_itemkey(sid,smkey,serial) values(24,7025,1001);
insert into t_itemkey(sid,smkey,serial) values(25,7026,1001);
insert into t_itemkey(sid,smkey,serial) values(26,7027,1001);
insert into t_itemkey(sid,smkey,serial) values(27,7028,1001);
insert into t_itemkey(sid,smkey,serial) values(28,7029,1001);
insert into t_itemkey(sid,smkey,serial) values(29,7030,1001);
insert into t_itemkey(sid,smkey,serial) values(30,7031,1001);
insert into t_itemkey(sid,smkey,serial) values(31,7032,1001);
insert into t_itemkey(sid,smkey,serial) values(32,7033,1001);
insert into t_itemkey(sid,smkey,serial) values(33,7034,1001);
insert into t_itemkey(sid,smkey,serial) values(34,7035,1001);
insert into t_itemkey(sid,smkey,serial) values(35,7036,1001);
insert into t_itemkey(sid,smkey,serial) values(36,7037,1001);
insert into t_itemkey(sid,smkey,serial) values(37,7038,1001);
insert into t_itemkey(sid,smkey,serial) values(38,7039,1001);
insert into t_itemkey(sid,smkey,serial) values(39,7040,1001);
insert into t_itemkey(sid,smkey,serial) values(40,7041,1001);
insert into t_itemkey(sid,smkey,serial) values(41,7042,1001);
insert into t_itemkey(sid,smkey,serial) values(42,7043,1001);
insert into t_itemkey(sid,smkey,serial) values(43,7044,1001);
insert into t_itemkey(sid,smkey,serial) values(44,7045,1001);
insert into t_itemkey(sid,smkey,serial) values(45,7046,1001);



/*==============================================================*/
/* Index: Index_itk_sid                                         */
/*==============================================================*/
create index Index_itk_sid on t_itemkey
(
   sid
);

/*==============================================================*/
/* Table: t_mail                                                */
/*==============================================================*/
create table if not exists t_mail
(
   aid                            bigint                         not null AUTO_INCREMENT,
   sender                         varchar(50)                    not null,
   recer                          varchar(50)                    not null,
   mailinfo                       varchar(100)                   not null,
   mailcont                       text                           not null,
   pindex                         int                            not null,
   isvalid                        int                            not null default 0,
   primary key (aid)
);

delimiter //
drop procedure save_mailinfo//
create procedure save_mailinfo(p1 varchar(50),p2 varchar(50),p3 varchar(100),p4 varchar(300),p5 int,p6 int)
begin
declare rcount int;
start transaction;
select pindex into rcount from t_mail where pindex = p5;
if rcount = p5 then
        update t_mail set sender=p1,recer=p2,mailinfo=p3,
            mailcont=p4,isvalid=p6 where pindex=p5;
else
        insert into t_mail(pindex,sender,recer,mailinfo,mailcont,isvalid)
          values(p5,p1,p2,p3,p4,p6);
end if;
commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_mail_mail                                       */
/*==============================================================*/
create unique index Index_mail_mail on t_mail
(
   pindex
);

/*==============================================================*/
/* Table: t_mission             任务                                */
/*==============================================================*/
create table if not exists t_mission
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   missionid                      int                            not null,
   scriptid                       int                            not null,
   flag                           smallint                       not null,
   p1                             int                            not null,
   p2                             int                            not null,
   p3                             int                            not null,
   p4                             int                            not null,
   p5                             int                            not null,
   p6                             int                            not null,
   p7                             int                            not null,
   p8                             int                            not null,
   dbversion                      int                            default 0,
   isvalid                        int                            default 1,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_mi_charguid                                     */
/*==============================================================*/
create index Index_mi_charguid on t_mission
(
   charguid
);

/*==============================================================*/
/* Table: t_pet  珍兽属性                                       */
/*==============================================================*/
create table if not exists t_pet
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   hpetguid                       int                            not null,
   lpetguid                       int                            not null,
   dataxid                        int                            not null,
   dataid                         int                            not null,
   petname                        varchar(50)                    not null,
   petnick                        varchar(50)                    not null,
   level                          int                            not null,
   needlevel                      int                            not null,
   atttype                        int                            not null,
   aitype                         int                            not null,
   camp                           varchar(30)                    not null,
   hp                             int                            not null,
   mp                             int                            not null,
   life                           int                            not null,
   pettype                        smallint                       not null,
   genera                         smallint                       not null,
   enjoy                          smallint                       not null,
   strper                         int                            not null,
   conper                         int                            not null,
   dexper                         int                            not null,
   sprper                         int                            not null,
   iprper                         int                            not null,
   gengu                          int                            not null,
   growrate                       int                            not null,
   repoint                        int                            not null,
   exp                            int                            not null,
   str                            int                            not null,
   con                            int                            not null,
   dex                            int                            not null,
   spr                            int                            not null,
   ipr                            int                            not null,
   skill                          varchar(50)                    not null,
   dbversion                      int                            default 0,
   flags                          int,
   isvalid                        int                            default 1,
   pwflag                         int                            default 0,
   pclvl                          int                            default 0,
   hspetguid                      int                            default 0,
   lspetguid                      int                            default 0,
   savvy                          int                            default 0,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_Pet_Charguid                                    */
/*==============================================================*/
create index Index_Pet_Charguid on t_pet
(
   charguid
);

/*==============================================================*/
/* Table: t_petcreate                                           */
/*==============================================================*/
create table if not exists t_petcreate
(
   aid                            bigint                         not null AUTO_INCREMENT,
   pindex                         int                            not null,
   pairdata                       text                           not null,
   isvalid                        int                            not null,
   primary key (aid)
);

delimiter //
drop procedure save_petiteminfo//
create procedure save_petiteminfo(ppairdata text,ppoolid int,pisvalid int)
begin
declare rcount int;
start transaction;
select pindex into rcount from t_petcreate where pindex = ppoolid;
if rcount = ppoolid then
        update t_petcreate set pairdata=ppairdata,isvalid=pisvalid
                where pindex=ppoolid;
else
        insert into t_petcreate(pindex,pairdata,isvalid)  
        values(ppoolid,ppairdata,pisvalid);    
end if;
commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_pcre_pindex                                     */
/*==============================================================*/
create index Index_pcre_pindex on t_petcreate
(
   pindex
);

/*==============================================================*/
/* Table: t_pshop                                               */
/*==============================================================*/
create table if not exists t_pshop
(
   aid                            bigint                         not null AUTO_INCREMENT,
   sid                            int                            not null,
   poolid                         int                            not null,
   shopguid                       varchar(50)                    not null,
   type                         int                            not null,
   stat                           int                            not null,
   maxbmoney                      int                            not null,
   basemoney                      int                            not null,
   createtime                     int                            not null,
   shopname                       varchar(50)                    not null,
   shopdesc                       varchar(50)                    not null,
   ownername                      varchar(50)                    not null,
   ownerguid                      int                            not null,
   isopen                         int                            not null,
   sale                           int                            not null,
   saleprice                      int                            not null,
   partner                        text                           not null,
   recoder                        longtext                       not null,
   stallinfo                      longtext                       not null,
   isvalid                        int                            not null,
   partnum                        int                            not null,
   subtype                        int                            not null,
   profit                         int                            not null,
   buyinfo                        longtext                       not null default '',
   primary key (aid)
);

delimiter //
drop procedure save_shopinfo//
create procedure save_shopinfo(
psid                  int,
ppoolid               int,
pshopguid             varchar(50),
ptype                 int,
pstat                 int,
pmaxbmoney            int,
pbasemoney            int,
pprofit               int,
pcreatetime           int,
pshopname             varchar(50),
pshopdesc             varchar(50),
pownername            varchar(50),
pownerguid            int,
pisopen               int,
psale                 int,
psaleprice            int,
ppartner              text,
pisvalid              int,
ppartnum              int,
subtype               int)
begin
declare rcount int;
declare rindex int;
start transaction;
select sid ,poolid into rcount,rindex from t_pshop where sid = psid and poolid=ppoolid;
if rcount = psid then
        update t_pshop set  shopguid=pshopguid,
                            type=ptype,
                            stat=pstat,
                            maxbmoney=pmaxbmoney,
                            basemoney=pbasemoney,
                            profit   =pprofit,
                            createtime=pcreatetime,
                            shopname=pshopname,
                            shopdesc=pshopdesc,
                            ownername=pownername,
                            ownerguid=pownerguid,
                            isopen=pisopen,
                            sale=psale,
                            saleprice=psaleprice,
                            partner=ppartner,
                            isvalid=pisvalid,
                            partnum=ppartnum,
                            subtype=subtype 
                            where sid=psid and poolid=ppoolid;
else
        insert into t_pshop(sid,       
                            poolid,    
                            shopguid,  
                            type,      
                            stat,      
                            maxbmoney, 
                            basemoney, 
                            profit,
                            createtime,
                            shopname,  
                            shopdesc,  
                            ownername, 
                            ownerguid, 
                            isopen,    
                            sale,      
                            saleprice, 
                            partner,
                            recoder,
                            stallinfo,   
                            isvalid,   
                            partnum,
                            subtype)    values
                            (psid,       
                             ppoolid,    
                             pshopguid,  
                             ptype,      
                             pstat,      
                             pmaxbmoney, 
                             pbasemoney, 
                             pprofit,
                             pcreatetime,
                             pshopname,  
                             pshopdesc,  
                             pownername, 
                             pownerguid, 
                             pisopen,    
                             psale,      
                             psaleprice,
                             ppartner,
                             '',
                             '',   
                             pisvalid,   
                             ppartnum,
                             subtype); 
end if;
commit;
end;//
delimiter ;
/*==============================================================*/
/* Index: Index_pshop_shopguid                                  */
/*==============================================================*/
create index Index_pshop_shopguid on t_pshop
(
   shopguid
);

/*==============================================================*/
/* Index: Index_pshop_sidpid                                    */
/*==============================================================*/
create index Index_pshop_sidpid on t_pshop
(
   sid,
   poolid
);

/*==============================================================*/
/* Table: t_relation             关系信息                               */
/*==============================================================*/
create table if not exists t_relation
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   fguid                          int                            not null,
   fname                          varchar(50)                    not null,
   fpoint                         int                            not null,
   reflag                         smallint                       not null,
   groupid                        smallint                       not null,
   extdata                        varchar(100)                   not null,
   dbversion                      int                            default 0,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_re_charguid                                     */
/*==============================================================*/
create index Index_re_charguid on t_relation
(
   charguid
);

/*==============================================================*/
/* Table: t_skill                                               */
/*==============================================================*/
create table if not exists t_skill
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   skid                           smallint                       not null,
   sktime                         int,
   dbversion                      int                            default 0,
   isvalid                        int,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_sk_charguid                                     */
/*==============================================================*/
create index Index_sk_charguid on t_skill
(
   charguid
);

/*==============================================================*/
/* Table: t_var                                                 */
/*==============================================================*/
create table if not exists t_var
(
   maxcharguid                    int                            not null,
   primary key (maxcharguid)
);

delimiter //
drop procedure fetch_guid //
create procedure fetch_guid()
begin
declare charguid  int default -1;
start transaction;
select t_var.maxcharguid into charguid from t_var limit 1; 
if charguid<>-1 then
    update t_var set t_var.maxcharguid = charguid+1 where t_var.maxcharguid=charguid;
end if;
commit;
select charguid;
end;//
delimiter ;

insert into t_var values(1010000001);
/*==============================================================*/
/* Table: t_xfallexp                                            */
/*==============================================================*/
create table if not exists t_xfallexp
(
   xflv                           int                            not null,
   id1all                         int                            not null,
   id2all                         int                            not null,
   id3all                         int                            not null,
   id4all                         int                            not null,
   id5all                         int                            not null,
   id6all                         int                            not null,
   id7all                         int                            not null,
   primary key (xflv)
);

insert into t_xfallexp values(1,11,11,23,8,23,23,23);
insert into t_xfallexp values(2,52,52,104,35,104,104,104);
insert into t_xfallexp values(3,131,131,262,88,262,262,262);
insert into t_xfallexp values(4,275,275,550,184,550,550,550);
insert into t_xfallexp values(5,498,498,996,333,996,996,996);
insert into t_xfallexp values(6,824,824,1649,551,1649,1649,1649);
insert into t_xfallexp values(7,1282,1282,2566,857,2566,2566,2566);
insert into t_xfallexp values(8,1903,1903,3808,1271,3808,3808,3808);
insert into t_xfallexp values(9,2605,2605,5212,1739,5212,5212,5212);
insert into t_xfallexp values(10,3393,3393,6787,2264,6787,6787,6787);
insert into t_xfallexp values(11,4271,4271,8542,2849,8542,8542,8542);
insert into t_xfallexp values(12,5243,5243,10486,3497,10486,10486,10486);
insert into t_xfallexp values(13,6352,6352,12705,4237,12705,12705,12705);
insert into t_xfallexp values(14,7608,7608,15216,5074,15216,15216,15216);
insert into t_xfallexp values(15,9062,9062,18123,6043,18123,18123,18123);
insert into t_xfallexp values(16,10727,10727,21453,7153,21453,21453,21453);
insert into t_xfallexp values(17,12664,12664,25328,8445,25328,25328,25328);
insert into t_xfallexp values(18,14941,14941,29882,9963,29882,29882,29882);
insert into t_xfallexp values(19,17632,17632,35264,11757,35264,35264,35264);
insert into t_xfallexp values(20,20818,20818,41636,13881,41636,41636,41636);
insert into t_xfallexp values(21,24587,24587,49174,16394,49174,49174,49174);
insert into t_xfallexp values(22,29033,29033,58066,19358,58066,58066,58066);
insert into t_xfallexp values(23,34258,34258,68515,22841,68515,68515,68515);
insert into t_xfallexp values(24,40369,40369,80737,26915,80737,80737,80737);
insert into t_xfallexp values(25,47547,47547,95092,31700,95092,95092,95092);
insert into t_xfallexp values(26,55985,55985,111967,37325,111967,111967,111967);
insert into t_xfallexp values(27,65820,65820,131637,43882,131637,131637,131637);
insert into t_xfallexp values(28,77196,77196,154389,51466,154389,154389,154389);
insert into t_xfallexp values(29,90264,90264,180525,60178,180525,180525,180525);
insert into t_xfallexp values(30,105717,105717,211431,70480,211431,211431,211431);
insert into t_xfallexp values(31,123751,123751,247499,82503,247499,247499,247499);
insert into t_xfallexp values(32,144568,144568,289133,96381,289133,289133,289133);
insert into t_xfallexp values(33,168378,168378,336752,112254,336752,336752,336752);
insert into t_xfallexp values(34,195396,195396,390788,130266,390788,390788,390788);
insert into t_xfallexp values(35,225845,225845,451687,150566,451687,451687,451687);
insert into t_xfallexp values(36,259955,259955,519907,173306,519907,519907,519907);
insert into t_xfallexp values(37,297962,297962,595921,198644,595921,595921,595921);
insert into t_xfallexp values(38,340109,340109,680215,226742,680215,680215,680215);
insert into t_xfallexp values(39,386646,386646,773289,257767,773289,773289,773289);
insert into t_xfallexp values(40,437879,437879,875754,291922,875754,875754,875754);
insert into t_xfallexp values(41,494124,494124,988244,329419,988244,988244,988244);
insert into t_xfallexp values(42,555707,555707,1111409,370474,1111409,1111409,1111409);
insert into t_xfallexp values(43,622964,622964,1245923,415312,1245923,1245923,1245923);
insert into t_xfallexp values(44,696242,696242,1392479,464164,1392479,1392479,1392479);
insert into t_xfallexp values(45,775898,775898,1551791,517268,1551791,1551791,1551791);
insert into t_xfallexp values(46,862298,862298,1724591,574868,1724591,1724591,1724591);
insert into t_xfallexp values(47,955819,955819,1911634,637216,1911634,1911634,1911634);
insert into t_xfallexp values(48,1056849,1056849,2113693,704569,2113693,2113693,2113693);
insert into t_xfallexp values(49,1165784,1165784,2331564,777193,2331564,2331564,2331564);
insert into t_xfallexp values(50,1283032,1283032,2566059,855358,2566059,2566059,2566059);
insert into t_xfallexp values(51,1409010,1409010,2818014,939343,2818014,2818014,2818014);
insert into t_xfallexp values(52,1544145,1544145,3088284,1029433,3088284,3088284,3088284);
insert into t_xfallexp values(53,1688876,1688876,3377745,1125920,3377745,3377745,3377745);
insert into t_xfallexp values(54,1843649,1843649,3687291,1229102,3687291,3687291,3687291);
insert into t_xfallexp values(55,2008923,2008923,4017839,1339285,4017839,4017839,4017839);
insert into t_xfallexp values(56,2185166,2185166,4370324,1456780,4370324,4370324,4370324);
insert into t_xfallexp values(57,2372856,2372856,4745704,1581907,4745704,4745704,4745704);
insert into t_xfallexp values(58,2572481,2572481,5144953,1714990,5144953,5144953,5144953);
insert into t_xfallexp values(59,2784539,2784539,5569069,1856362,5569069,5569069,5569069);
insert into t_xfallexp values(60,3009539,3009539,6019069,2006362,6019069,6019069,6019069);
insert into t_xfallexp values(61,3248000,3248000,6495991,2165336,6495991,6495991,6495991);
insert into t_xfallexp values(62,3500450,3500450,7000891,2333636,7000891,7000891,7000891);
insert into t_xfallexp values(63,3767428,3767428,7534848,2511622,7534848,7534848,7534848);
insert into t_xfallexp values(64,4049484,4049484,8098959,2699659,8098959,8098959,8098959);
insert into t_xfallexp values(65,4347176,4347176,8694344,2898121,8694344,8694344,8694344);
insert into t_xfallexp values(66,4661782,4661782,9323557,3107859,9323557,9323557,9323557);
insert into t_xfallexp values(67,4995261,4995261,9990514,3330178,9990514,9990514,9990514);
insert into t_xfallexp values(68,5349636,5349636,10699264,3566428,10699264,10699264,10699264);
insert into t_xfallexp values(69,5727001,5727001,11453994,3818005,11453994,11453994,11453994);
insert into t_xfallexp values(70,6129515,6129515,12259022,4086348,12259022,12259022,12259022);
insert into t_xfallexp values(71,6559406,6559406,13118804,4372942,13118804,13118804,13118804);
insert into t_xfallexp values(72,7018969,7018969,14037929,4679317,14037929,14037929,14037929);
insert into t_xfallexp values(73,7510566,7510566,15021124,5007049,15021124,15021124,15021124);
insert into t_xfallexp values(74,8036627,8036627,16073247,5357757,16073247,16073247,16073247);
insert into t_xfallexp values(75,8601428,8601428,17202849,5734291,17202849,17202849,17202849);
insert into t_xfallexp values(76,9209378,9209378,18418749,6139591,18418749,18418749,18418749);
insert into t_xfallexp values(77,9865023,9865023,19730039,6576688,19730039,19730039,19730039);
insert into t_xfallexp values(78,10573042,10573042,21146077,7048701,21146077,21146077,21146077);
insert into t_xfallexp values(79,11338251,11338251,22676494,7558840,22676494,22676494,22676494);
insert into t_xfallexp values(80,12180719,12180719,24361429,8120485,24361429,24361429,24361429);
insert into t_xfallexp values(81,13140316,13140316,26280624,8760217,26280624,26280624,26280624);
insert into t_xfallexp values(82,14277612,14277612,28555217,9518415,28555217,28555217,28555217);
insert into t_xfallexp values(83,15674778,15674778,31349549,10449859,31349549,31349549,31349549);
insert into t_xfallexp values(84,17436483,17436483,34872959,11624329,34872959,34872959,34872959);
insert into t_xfallexp values(85,19690798,19690798,39381589,13127206,39381589,39381589,39381589);
insert into t_xfallexp values(86,22590092,22590092,45180177,15060069,45180177,45180177,45180177);
insert into t_xfallexp values(87,26311936,26311936,52623864,17541298,52623864,52623864,52623864);
insert into t_xfallexp values(88,31059999,31059999,62119989,20706673,62119989,62119989,62119989);
insert into t_xfallexp values(89,37064951,37064951,74129894,24709975,74129894,74129894,74129894);
insert into t_xfallexp values(90,44585362,44585362,89170717,29723583,89170717,89170717,89170717);
insert into t_xfallexp values(91,53908603,53908603,107817199,35939077,107817199,107817199,107817199);
insert into t_xfallexp values(92,65351743,65351743,130703479,43567837,130703479,130703479,130703479);
insert into t_xfallexp values(93,79262453,79262453,158524899,52841644,158524899,158524899,158524899);
insert into t_xfallexp values(94,96019902,96019902,192039797,64013277,192039797,192039797,192039797);
insert into t_xfallexp values(95,116035661,116035661,232071314,77357116,232071314,232071314,232071314);
insert into t_xfallexp values(96,139754599,139754599,279509189,93169741,279509189,279509189,279509189);
insert into t_xfallexp values(97,167655786,167655786,335311564,111770533,335311564,335311564,335311564);
insert into t_xfallexp values(98,200253392,200253392,400506777,133502271,400506777,400506777,400506777);
insert into t_xfallexp values(99,238097588,238097588,476195169,158731735,476195169,476195169,476195169);
insert into t_xfallexp values(100,239313265,239313265,479234361,159947412,479234361,479234361,479234361);
insert into t_xfallexp values(101,240560791,240560791,482353177,161194938,482353177,482353177,482353177);
insert into t_xfallexp values(102,241840550,241840550,485552575,162474697,485552575,485552575,485552575);
insert into t_xfallexp values(103,243152927,243152927,488833517,163787074,488833517,488833517,488833517);
insert into t_xfallexp values(104,244498305,244498305,492196961,165132452,492196961,492196961,492196961);
insert into t_xfallexp values(105,245877068,245877068,495643869,166511215,495643869,495643869,495643869);
insert into t_xfallexp values(106,247289600,247289600,499175199,167923747,499175199,499175199,499175199);
insert into t_xfallexp values(107,248736286,248736286,502791913,169370433,502791913,502791913,502791913);
insert into t_xfallexp values(108,250217508,250217508,506494969,170851655,506494969,506494969,506494969);
insert into t_xfallexp values(109,251733652,251733652,510285329,172367799,510285329,510285329,510285329);
insert into t_xfallexp values(110,253285101,253285101,514163951,173919248,514163951,514163951,514163951);
insert into t_xfallexp values(111,254872239,254872239,518131797,175506386,518131797,518131797,518131797);
insert into t_xfallexp values(112,256495450,256495450,522189825,177129597,522189825,522189825,522189825);
insert into t_xfallexp values(113,258155119,258155119,526338997,178789266,526338997,526338997,526338997);
insert into t_xfallexp values(114,259851629,259851629,530580271,180485776,530580271,530580271,530580271);
insert into t_xfallexp values(115,261585364,261585364,534914609,182219511,534914609,534914609,534914609);
insert into t_xfallexp values(116,263356708,263356708,539342969,183990855,539342969,539342969,539342969);
insert into t_xfallexp values(117,265166046,265166046,543866313,185800193,543866313,543866313,543866313);
insert into t_xfallexp values(118,267013760,267013760,548485599,187647907,548485599,548485599,548485599);
insert into t_xfallexp values(119,268900236,268900236,553201789,189534383,553201789,553201789,553201789);
insert into t_xfallexp values(120,270825857,270825857,558015841,191460004,558015841,558015841,558015841);

/*==============================================================*/
/* Table: t_xinfa              心法                                 */
/*==============================================================*/
create table if not exists t_xinfa
(
   aid                            bigint                         not null AUTO_INCREMENT,
   charguid                       int                            not null,
   xinfaid                        smallint                       not null,
   xinfalvl                       smallint                       not null,
   dbversion                      int                            default 0,
   primary key (aid)
);

/*==============================================================*/
/* Index: Index_xinfa_charguid                                  */
/*==============================================================*/
create index Index_xinfa_charguid on t_xinfa
(
   charguid
);



alter table t_ability   engine=innodb;
alter table t_char      engine=innodb;
alter table t_city      engine=innodb;
alter table t_guild     engine=innodb;
alter table t_impact    engine=innodb;
alter table t_iteminfo  engine=innodb;
alter table t_itemkey   engine=innodb;
alter table t_mail      engine=innodb;
alter table t_mission   engine=innodb;
alter table t_pet       engine=innodb;
alter table t_petcreate engine=innodb;
alter table t_pshop     engine=innodb;
alter table t_relation  engine=innodb;
alter table t_skill     engine=innodb;
alter table t_var       engine=innodb;
alter table t_xinfa     engine=innodb;

alter table t_xfallexp  engine=myisam;
alter table t_crc32     engine=myisam;
alter table t_global    engine=myisam;
alter table t_charextra engine=innodb;
alter table t_cshop     engine=innodb;
alter table t_cshopitem engine=innodb;

--1.top 50 level character
delimiter //
drop procedure get_50level_list //
create procedure get_50level_list()
begin
 select accname,charguid,charname,menpai,level,exp 
 from t_char 
 where charname not like '%DELETE%'
 order by level desc, exp desc
 limit 50;
end//
delimiter ;

--2.top 50 xinfa character
delimiter //
drop procedure get_50xinfa_list //
create procedure get_50xinfa_list()
begin
 drop table if exists tmp_xinfa;
 create temporary table tmp_xinfa
 (charguid int not null,
  totalexp bigint not null
 )engine=myisam;
 
 insert into tmp_xinfa
 select a.charguid,sum(
  case mod(a.xinfaid,6)
   when 1 then b.id1all
   when 2 then b.id2all
   when 3 then b.id3all
   when 4 then b.id4all
   when 5 then b.id5all
   when 0 then b.id6all
   else b.id7all
  end
  ) as totalexp
 from t_xinfa as a left join t_xfallexp as b
  on a.xinfalvl=b.xflv
 where a.charguid in(
 select charguid from t_char where charname not like '%DELETE%'
 )
 group by a.charguid
 order by totalexp desc
 limit 50;
 
 select a.accname,b.charguid,a.charname,a.menpai,a.exp,b.totalexp
 from t_char as a,tmp_xinfa as b 
 where b.charguid=a.charguid
 order by b.totalexp desc, a.exp desc;
 
 drop table if exists tmp_xinfa;
end//
delimiter ;

--3.top 50 money character
delimiter //
drop procedure get_50money_list //
create procedure get_50money_list()
begin
 select a.accname,a.charguid,a.charname,a.menpai, 
  (a.vmoney+a.bankmoney+if(isnull(b.profit),0,b.profit)) as totalmoney
 from t_char as a left join t_pshop as b
  on a.charguid=b.ownerguid 
 where a.charname not like '%DELETE%'
 order by totalmoney desc 
 limit 50;
end//
delimiter ;

--4.method of create character
delimiter //
drop procedure create_newchar//
create procedure create_newchar(
paccname              varchar(50) binary,
pcharname             varchar(50) binary,
psex                  smallint,
pcreatetime           int,
phaircolor            int,
phairmodel            int,
pfacecolor            int,
pfacemodel            int,
pheadid               int,
pdefeq                int)
begin

declare rguid            int default -1;
declare result          int default -1;
start transaction; 
 select charguid into rguid from t_char where charname=pcharname limit 1;
 if found_rows() = 0 then
  set rguid = -1;
  update t_var set maxcharguid=maxcharguid+1;
  select maxcharguid into rguid from t_var limit 1;
  
  if rguid <> -1 then
   insert into t_char(accname,charguid,charname,title,pw,sex,level,enegry,outlook,scene,xpos,zpos,menpai,
    hp,mp,strikepoint,str,con,dex,spr,ipr,points,logouttime,logintime,createtime,dbversion,haircolor,
    hairmodel,facecolor,facemodel,vmoney,settings,isvalid,exp,pres,
    shopinfo,carrypet,guldid,teamid,headid,erecover,vigor,maxvigor,vrecover,energymax,pwdeltime,
    pinfo,bkscene,bkxpos,bkzpos,titleinfo,dietime,bankmoney,bankend,cooldown,defeq)
   values(paccname,rguid,pcharname,'','',psex,1,0,0,0,100,100,9,
    5000,5000,0,5,5,5,5,5,0,0,0,pcreatetime,0,phaircolor,
    phairmodel,pfacecolor,pfacemodel,0,'',1,0,'',
        '','',-1,-1,pheadid,0,0,0,0,0,0,
        '',0,0,0,'',0,0,20,'',pdefeq);
   select row_count() into result;
  else
   set result = -3; 
  end if;
 else
   set result = -2;    
 end if;
commit;
select result,rguid;
end//
delimiter ;

--5.method of cacultotal
delimiter //
drop procedure cacultotal//
create procedure cacultotal(
lowindex        int,
highindex       int)
begin

declare lowvalue  int;
declare highvalue int;

set lowvalue = 0;
set highvalue = 0;

select data1 into lowvalue from t_global where poolid=lowindex;
select data1 into highvalue from t_global where poolid=highindex;

select sum(highvalue*2000000000+lowvalue) as total;

end;//
delimiter ;
