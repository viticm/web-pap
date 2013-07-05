/* 2007-05-30 */
/* 创建用于统计天龙八部各种数据的数据库，以及若干表 */
/* Create Database tlbbdb_stat and several tables */
drop database if exists tlbbdb_stat;
create database if not exists tlbbdb_stat;
use tlbbdb_stat;

/* [tables create] tlbbdb_stat. */
CREATE TABLE if not exists tlbb_charcount (
  man int default 0,
	female int default 0,
	shaolin int default 0,
	mingjiao int default 0,
	gaibang int default 0,
	wudang int default 0,
	emei int default 0,
	xingxiu int default 0,
	dali int default 0,
	tianshan int default 0,
	xiaoyao int default 0,
	wumenpai int default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_moneycount (
	totalmoney bigint default 0,
	createmoney bigint default 0,
	costmoney bigint default 0,
	gmcreatemoney bigint default 0,
	totalyuanbao bigint default 0,
	createyuanbao bigint default 0,
	costyuanbao bigint default 0,
	gmcreateyuanbao bigint default 0,
	createzengdian bigint default 0,
	costzengdian bigint default 0,
	gmcreatezengdian bigint default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_gemcount (
	itemname char(30) not null,
	itemcount int default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_geminfo (
	itemcode int default 0,
	itemname char(30) not null
);

CREATE TABLE if not exists tlbb_moneylist (
	accname varchar(50) binary not null,
	charname varchar(50) binary not null,
	level int default 1,
	vmoney int default 0,
	bankmoney int default 0,
	totalmoney int default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_get50levellist (
	accname varchar(50) binary not null,
	charguid int default 0,
	charname varchar(50) binary not null,
	menpai varchar(10) binary not null,
	level int default 1,
	exp int default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_get50xinfalist (
	accname varchar(50) binary not null,
	charguid int default 0,
	charname varchar(50) binary not null,
	menpai varchar(10) binary not null,
	exp int default 0,
	totalexp bigint default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_get50moneylist (
	accname varchar(50) binary not null,
	charguid int default 0,
	charname varchar(50) binary not null,
	menpai varchar(10) binary not null,
	totalmoney bigint default 0,
	counttime timestamp default now() not null
);

CREATE TABLE if not exists tlbb_menpaiinfo (
	menpai smallint default 9,
	menpainame varchar(10) binary not null
);

alter table tlbb_charcount   engine=innodb;
alter table tlbb_gemcount   engine=innodb;
alter table tlbb_geminfo   engine=innodb;
alter table tlbb_moneylist   engine=innodb;
alter table tlbb_get50levellist   engine=innodb;
alter table tlbb_get50xinfalist   engine=innodb;
alter table tlbb_get50moneylist   engine=innodb;
alter table tlbb_menpaiinfo   engine=innodb;

insert into tlbb_geminfo(itemcode, itemname)
values (50101001,"猫眼石（1级）"),
(50101002,"虎眼石（1级）"),
(50102001,"黄晶石（1级）"),
(50102002,"蓝晶石（1级）"),
(50102003,"红晶石（1级）"),
(50102004,"绿晶石（1级）"),
(50103001,"紫玉（1级）"),
(50104002,"变石（1级）"),
(50111001,"石榴石（1级）"),
(50111002,"尖晶石（1级）"),
(50112001,"黄玉（1级）"),
(50112002,"皓石（1级）"),
(50112003,"月光石（1级）"),
(50112004,"碧玺（1级）"),
(50113001,"黄宝石（1级）"),
(50113002,"蓝宝石（1级）"),
(50113003,"绿宝石（1级）"),
(50113004,"红宝石（1级）"),
(50113005,"黑宝石（1级）"),
(50114001,"祖母绿（1级）"),
(50201001,"猫眼石（2级）"),
(50201002,"虎眼石（2级）"),
(50202001,"黄晶石（2级）"),
(50202002,"蓝晶石（2级）"),
(50202003,"红晶石（2级）"),
(50202004,"绿晶石（2级）"),
(50203001,"紫玉（2级）"),
(50204002,"变石（2级）"),
(50211001,"石榴石（2级）"),
(50211002,"尖晶石（2级）"),
(50212001,"黄玉（2级）"),
(50212002,"皓石（2级）"),
(50212003,"月光石（2级）"),
(50212004,"碧玺（2级）"),
(50213001,"黄宝石（2级）"),
(50213002,"蓝宝石（2级）"),
(50213003,"绿宝石（2级）"),
(50213004,"红宝石（2级）"),
(50213005,"黑宝石（2级）"),
(50214001,"祖母绿（2级）"),
(50301001,"猫眼石（3级）"),
(50301002,"虎眼石（3级）"),
(50302001,"黄晶石（3级）"),
(50302002,"蓝晶石（3级）"),
(50302003,"红晶石（3级）"),
(50302004,"绿晶石（3级）"),
(50303001,"紫玉（3级）"),
(50304002,"变石（3级）"),
(50311001,"石榴石（3级）"),
(50311002,"尖晶石（3级）"),
(50312001,"黄玉（3级）"),
(50312002,"皓石（3级）"),
(50312003,"月光石（3级）"),
(50312004,"碧玺（3级）"),
(50313001,"黄宝石（3级）"),
(50313002,"蓝宝石（3级）"),
(50313003,"绿宝石（3级）"),
(50313004,"红宝石（3级）"),
(50313005,"黑宝石（3级）"),
(50314001,"祖母绿（3级）"),
(50401001,"猫眼石（4级）"),
(50401002,"虎眼石（4级）"),
(50402001,"黄晶石（4级）"),
(50402002,"蓝晶石（4级）"),
(50402003,"红晶石（4级）"),
(50402004,"绿晶石（4级）"),
(50403001,"紫玉（4级）"),
(50404002,"变石（4级）"),
(50411001,"石榴石（4级）"),
(50411002,"尖晶石（4级）"),
(50412001,"黄玉（4级）"),
(50412002,"皓石（4级）"),
(50412003,"月光石（4级）"),
(50412004,"碧玺（4级）"),
(50413001,"黄宝石（4级）"),
(50413002,"蓝宝石（4级）"),
(50413003,"绿宝石（4级）"),
(50413004,"红宝石（4级）"),
(50413005,"黑宝石（4级）"),
(50414001,"祖母绿（4级）"),
(50501001,"猫眼石（5级）"),
(50501002,"虎眼石（5级）"),
(50502001,"黄晶石（5级）"),
(50502002,"蓝晶石（5级）"),
(50502003,"红晶石（5级）"),
(50502004,"绿晶石（5级）"),
(50503001,"紫玉（5级）"),
(50504002,"变石（5级）"),
(50511001,"石榴石（5级）"),
(50511002,"尖晶石（5级）"),
(50512001,"黄玉（5级）"),
(50512002,"皓石（5级）"),
(50512003,"月光石（5级）"),
(50512004,"碧玺（5级）"),
(50513001,"黄宝石（5级）"),
(50513002,"蓝宝石（5级）"),
(50513003,"绿宝石（5级）"),
(50513004,"红宝石（5级）"),
(50513005,"黑宝石（5级）"),
(50514001,"祖母绿（5级）"),
(50601001,"猫眼石（6级）"),
(50601002,"虎眼石（6级）"),
(50602001,"黄晶石（6级）"),
(50602002,"蓝晶石（6级）"),
(50602003,"红晶石（6级）"),
(50602004,"绿晶石（6级）"),
(50603001,"紫玉（6级）"),
(50604002,"变石（6级）"),
(50611001,"石榴石（6级）"),
(50611002,"尖晶石（6级）"),
(50612001,"黄玉（6级）"),
(50612002,"皓石（6级）"),
(50612003,"月光石（6级）"),
(50612004,"碧玺（6级）"),
(50613001,"黄宝石（6级）"),
(50613002,"蓝宝石（6级）"),
(50613003,"绿宝石（6级）"),
(50613004,"红宝石（6级）"),
(50613005,"黑宝石（6级）"),
(50614001,"祖母绿（6级）"),
(50701001,"猫眼石（7级）"),
(50701002,"虎眼石（7级）"),
(50702001,"黄晶石（7级）"),
(50702002,"蓝晶石（7级）"),
(50702003,"红晶石（7级）"),
(50702004,"绿晶石（7级）"),
(50703001,"紫玉（7级）"),
(50704002,"变石（7级）"),
(50711001,"石榴石（7级）"),
(50711002,"尖晶石（7级）"),
(50712001,"黄玉（7级）"),
(50712002,"皓石（7级）"),
(50712003,"月光石（7级）"),
(50712004,"碧玺（7级）"),
(50713001,"黄宝石（7级）"),
(50713002,"蓝宝石（7级）"),
(50713003,"绿宝石（7级）"),
(50713004,"红宝石（7级）"),
(50713005,"黑宝石（7级）"),
(50714001,"祖母绿（7级）"),
(50801001,"猫眼石（8级）"),
(50801002,"虎眼石（8级）"),
(50802001,"黄晶石（8级）"),
(50802002,"蓝晶石（8级）"),
(50802003,"红晶石（8级）"),
(50802004,"绿晶石（8级）"),
(50803001,"紫玉（8级）"),
(50804002,"变石（8级）"),
(50811001,"石榴石（8级）"),
(50811002,"尖晶石（8级）"),
(50812001,"黄玉（8级）"),
(50812002,"皓石（8级）"),
(50812003,"月光石（8级）"),
(50812004,"碧玺（8级）"),
(50813001,"黄宝石（8级）"),
(50813002,"蓝宝石（8级）"),
(50813003,"绿宝石（8级）"),
(50813004,"红宝石（8级）"),
(50813005,"黑宝石（8级）"),
(50814001,"祖母绿（8级）"),
(50901001,"猫眼石（9级）"),
(50901002,"虎眼石（9级）"),
(50902001,"黄晶石（9级）"),
(50902002,"蓝晶石（9级）"),
(50902003,"红晶石（9级）"),
(50902004,"绿晶石（9级）"),
(50903001,"紫玉（9级）"),
(50904002,"变石（9级）"),
(50911001,"石榴石（9级）"),
(50911002,"尖晶石（9级）"),
(50912001,"黄玉（9级）"),
(50912002,"皓石（9级）"),
(50912003,"月光石（9级）"),
(50912004,"碧玺（9级）"),
(50913001,"黄宝石（9级）"),
(50913002,"蓝宝石（9级）"),
(50913003,"绿宝石（9级）"),
(50913004,"红宝石（9级）"),
(50913005,"黑宝石（9级）"),
(50914001,"祖母绿（9级）");

insert into tlbb_menpaiinfo(menpai, menpainame)
values (0,"少林"),
(1,"明教"),
(2,"丐帮"),
(3,"武当"),
(4,"峨嵋"),
(5,"星宿"),
(6,"天龙"),
(7,"天山"),
(8,"逍遥"),
(9,"无门派");

/* 2007-05-30 */
/* 本组服务器男性角色、女性角色数量，各门派以及无门派角色数量，各等级角色数量统计情况 */
/* [proc] tlbbdb_stat.tlbb_charcount_pro */
use tlbbdb_stat;
DELIMITER //

DROP PROCEDURE IF EXISTS `tlbbdb_stat`.`tlbb_charcount_pro` //

CREATE PROCEDURE tlbb_charcount_pro()
BEGIN
  declare man int default 0;
  declare female int default 0;
  declare dali int default 0;
  declare shaolin int default 0;
  declare wudang int default 0;
  declare emei int default 0;
  declare mingjiao int default 0;
  declare gaibang int default 0;
  declare xingxiu int default 0;
  declare xiaoyao int default 0;
  declare tianshan int default 0;
  declare wumenpai int default 0;
	declare lowvalue int default 0;
  declare highvalue int default 0;

  /* truncate table tlbb_charcount; */

  select count(sex) into man from tlbbdb.t_char where sex = 1 and isvalid = 1;
  select count(sex) into female from tlbbdb.t_char where sex = 0 and isvalid = 1;
  select count(menpai) into shaolin from tlbbdb.t_char where menpai = 0 and isvalid = 1;
  select count(menpai) into mingjiao from tlbbdb.t_char where menpai = 1 and isvalid = 1;
  select count(menpai) into gaibang from tlbbdb.t_char where menpai = 2 and isvalid = 1;
  select count(menpai) into wudang from tlbbdb.t_char where menpai = 3 and isvalid = 1;
  select count(menpai) into emei from tlbbdb.t_char where menpai = 4 and isvalid = 1;
  select count(menpai) into xingxiu from tlbbdb.t_char where menpai = 5 and isvalid = 1;
  select count(menpai) into dali from tlbbdb.t_char where menpai = 6 and isvalid = 1;
  select count(menpai) into tianshan from tlbbdb.t_char where menpai = 7 and isvalid = 1;
  select count(menpai) into xiaoyao from tlbbdb.t_char where menpai = 8 and isvalid = 1;
  select count(menpai) into wumenpai from tlbbdb.t_char where menpai = 9 and isvalid = 1;

  /* start transaction; */

  insert into tlbb_charcount(man,female,shaolin,mingjiao,gaibang,wudang,emei,xingxiu,dali,tianshan,xiaoyao,wumenpai)
  values (man,female,shaolin,mingjiao,gaibang,wudang,emei,xingxiu,dali,tianshan,xiaoyao,wumenpai);

  /* commit; */

END //

DELIMITER ;

/* 2007-06-03 */
/* 本组服务器金钱总数、生成的金钱总数、消耗的金钱总数、GM补偿的金钱总数、元宝总数、生成的元宝总数、消耗的元宝总数、
   GM补偿的元宝总数、生成的赠点总数、消耗的赠点总数、GM补偿的赠点总数统计情况 */
/* [proc] tlbbdb_stat.tlbb_moneycount_pro */
use tlbbdb_stat;
DELIMITER //

DROP PROCEDURE IF EXISTS `tlbbdb_stat`.`tlbb_moneycount_pro` //

CREATE PROCEDURE tlbb_moneycount_pro()
BEGIN
  declare vtotalmoney bigint default 0;
  declare vcountprofit int default 0;
	declare vcreatemoney bigint default 0;
	declare vcostmoney bigint default 0;
	declare vgmcreatemoney bigint default 0;
	declare vlowvalue int default 0;
  declare vhighvalue int default 0;

  /* truncate table tlbb_moneycount; */

  select (sum(vmoney*0.0001) + sum(bankmoney*0.0001)) into vtotalmoney from tlbbdb.t_char where isvalid = 1;
  select count(profit) into vcountprofit from tlbbdb.t_pshop;
  if vcountprofit > 0 then
    select (sum(profit*0.0001) + vtotalmoney) into vtotalmoney from tlbbdb.t_pshop where profit > 0;
  end if;
  select data1 into vlowvalue from tlbbdb.t_global where poolid=28;
  select data1 into vhighvalue from tlbbdb.t_global where poolid=29;
  select sum(vhighvalue*200000+vlowvalue*0.0001) into vcreatemoney;
  set vlowvalue = 0;
  set vhighvalue = 0;
  select data1 into vlowvalue from tlbbdb.t_global where poolid=30;
  select data1 into vhighvalue from tlbbdb.t_global where poolid=31;
  select sum(vhighvalue*200000+vlowvalue*0.0001) into vcostmoney;
  set vlowvalue = 0;
  set vhighvalue = 0;
  select data1 into vlowvalue from tlbbdb.t_global where poolid=32;
  select data1 into vhighvalue from tlbbdb.t_global where poolid=33;
  select sum(vhighvalue*200000+vlowvalue*0.0001) into vgmcreatemoney;

  /* start transaction; */

  update tlbb_moneycount set totalmoney=vtotalmoney,createmoney=vcreatemoney,costmoney=vcostmoney,gmcreatemoney=vgmcreatemoney
  where datediff(curdate(),counttime) = 0; 
  /* commit; */

END //

DELIMITER ;


/* 2007-06-13 */
/* 本组服务器元宝总数、生成的元宝总数、消耗的元宝总数、GM补偿的元宝总数、生成的赠点总数、消耗的赠点总数、GM补偿的赠点总数统计情况 */
/* [proc] tlbbdb_stat.tlbb_yuanbaocount_pro */
use tlbbdb_stat;
DELIMITER //

DROP PROCEDURE IF EXISTS `tlbbdb_stat`.`tlbb_yuanbaocount_pro` //

CREATE PROCEDURE tlbb_yuanbaocount_pro()
BEGIN
	declare totalyuanbao bigint default 0;
	declare createyuanbao bigint default 0;
	declare costyuanbao bigint default 0;
	declare gmcreateyuanbao bigint default 0;
	declare createzengdian bigint default 0;
	declare costzengdian bigint default 0;
	declare gmcreatezengdian bigint default 0;
	declare lowvalue int default 0;
  declare highvalue int default 0;
  declare yuanbaopoint bigint default 0;
  declare yuanbaoticket bigint default 0;

  /* truncate table tlbb_moneycount; */

  select sum(yuanbao) into yuanbaopoint from tlbbdb.t_char where isvalid = 1;
  select sum(p8) into yuanbaoticket from tlbbdb.t_iteminfo where itemtype = 30501036 and isvalid = 1;
  select sum(yuanbaopoint + yuanbaoticket) into totalyuanbao;  
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=22;
  select data1 into highvalue from tlbbdb.t_global where poolid=23;
  select sum(highvalue*2000000000+lowvalue) into createyuanbao;
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=24;
  select data1 into highvalue from tlbbdb.t_global where poolid=25;
  select sum(highvalue*2000000000+lowvalue) into costyuanbao;
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=26;
  select data1 into highvalue from tlbbdb.t_global where poolid=27;
  select sum(highvalue*2000000000+lowvalue) into gmcreateyuanbao;
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=34;
  select data1 into highvalue from tlbbdb.t_global where poolid=35;
  select sum(highvalue*2000000000+lowvalue) into createzengdian;
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=36;
  select data1 into highvalue from tlbbdb.t_global where poolid=37;
  select sum(highvalue*2000000000+lowvalue) into costzengdian;
  set lowvalue = 0;
  set highvalue = 0;
  select data1 into lowvalue from tlbbdb.t_global where poolid=38;
  select data1 into highvalue from tlbbdb.t_global where poolid=39;
  select sum(highvalue*2000000000+lowvalue) into gmcreatezengdian;

  /* start transaction; */

  insert into tlbb_moneycount(totalyuanbao,createyuanbao,costyuanbao,gmcreateyuanbao,createzengdian,costzengdian,gmcreatezengdian)
  values (totalyuanbao,createyuanbao,costyuanbao,gmcreateyuanbao,createzengdian,costzengdian,gmcreatezengdian);

  /* commit; */

END //

DELIMITER ;


/* 2007-03-17 */
/* 未被镶嵌的各种宝石数量统计情况 */
/* [proc] tlbbdb_stat.tlbb_gemcount_pro */
use tlbbdb_stat;
delimiter //

DROP PROCEDURE IF EXISTS `tlbbdb_stat`.`tlbb_gemcount_pro` //

CREATE PROCEDURE tlbb_gemcount_pro()
BEGIN
  declare itemname_s varchar(30);
  declare itemcode_i int default 0;
  declare itemcount_i int default 0;
  declare cursor_temp int default 0;

  declare itemcode_cursor cursor for
    select itemcode,itemname from tlbb_geminfo order by itemcode;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET cursor_temp = 1;

  set itemname_s = NULL;

  /* truncate table tlbb_gemcount; */

  /* start transaction; */

    open itemcode_cursor;
    REPEAT
      fetch itemcode_cursor into itemcode_i,itemname_s;
        select count(itemtype) into itemcount_i from tlbbdb.t_iteminfo where itemtype = itemcode_i;
        insert into tlbb_gemcount(itemname,itemcount) values(itemname_s,itemcount_i);
    UNTIL cursor_temp = 1 END REPEAT;
    close itemcode_cursor;

  /* commit; */

END //

delimiter ;

/* 2007-03-17 */
/* 本组服务器等级前50名角色的统计情况 */
/* The top 50 level character */
use tlbbdb_stat;
delimiter //
drop procedure IF EXISTS `tlbbdb_stat`.`tlbb_get50levellist_pro` //
create procedure tlbb_get50levellist_pro()
begin
 truncate table tlbb_get50levellist;

 insert into tlbb_get50levellist(accname,charguid,charname,menpai,level,exp)
 select accname,charguid,charname,menpai,level,exp
 from tlbbdb.t_char
 where isvalid = 1
 order by level desc, exp desc
 limit 50;

 update tlbb_get50levellist a, tlbb_menpaiinfo b set a.menpai=b.menpainame where a.menpai=b.menpai;

end//
delimiter ;


/* 2007-03-17 */
/* 本组服务器金钱前50名角色的统计情况 */
/* The top 50 money character */
use tlbbdb_stat;
delimiter //
drop procedure if exists `tlbbdb_stat`.`tlbb_get50moneylist_pro` //
create procedure tlbb_get50moneylist_pro()
begin
 truncate table tlbb_get50moneylist;

 insert into tlbb_get50moneylist(accname,charguid,charname,menpai,totalmoney)
 select a.accname,a.charguid,a.charname,a.menpai,
  (a.vmoney+a.bankmoney+sum(if(isnull(b.profit),0,b.profit))) as totalmoney
 from tlbbdb.t_char as a left join tlbbdb.t_pshop as b
  on a.charguid=b.ownerguid
 where a.isvalid = 1
 group by a.charguid
 order by totalmoney desc
 limit 50;

 update tlbb_get50moneylist a, tlbb_menpaiinfo b set a.menpai=b.menpainame where a.menpai=b.menpai;

end//
delimiter ;

/* 2007-03-17 */
/* 本组服务器心法前50名角色的统计情况 */
/* The top 50 xinfa character */
use tlbbdb_stat;
delimiter //
drop procedure if exists `tlbbdb_stat`.`tlbb_get50xinfalist_pro` //
create procedure tlbb_get50xinfalist_pro()
begin
 truncate table tlbb_get50xinfalist;

 drop table if exists tmp_xinfa;
 create temporary table tmp_xinfa
 (charguid int not null,
  totalexp bigint not null
 )engine=innodb;

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
 from tlbbdb.t_xinfa as a left join tlbbdb.t_xfallexp as b
  on a.xinfalvl=b.xflv
 where a.charguid in(
 select charguid from tlbbdb.t_char where isvalid = 1
 )
 group by a.charguid
 order by totalexp desc
 limit 50;

 insert into tlbb_get50xinfalist(accname,charguid,charname,menpai,exp,totalexp)
 select a.accname,b.charguid,a.charname,a.menpai,a.exp,b.totalexp
 from tlbbdb.t_char as a,tmp_xinfa as b
 where b.charguid=a.charguid
 order by b.totalexp desc, a.exp desc;

 drop table if exists tmp_xinfa;

 update tlbb_get50xinfalist a, tlbb_menpaiinfo b set a.menpai=b.menpainame where a.menpai=b.menpai;

end//
delimiter ;


/* 2007-03-17 */
/* （所有角色拥有的）金币总数大于10的帐号、帐号中等级最高的角色的（角色名称、等级、性别、门派）统计情况 */
/* [proc] tlbbdb_stat.tlbb_moneylist_pro */
use tlbbdb_stat;
DELIMITER //

DROP PROCEDURE IF EXISTS `tlbbdb_stat`.`tlbb_moneylist_pro` //

CREATE PROCEDURE tlbb_moneylist_pro()
BEGIN
  declare accname_s varchar(30);
  declare maxlevel_i int default 0;
  declare charname_s varchar(50);
  declare vmoney_i int default 0;
  declare bankmoney_i int default 0;
  declare shopmoney_i int default 0;
  declare totalmoney_i int default 0;
  declare cursor_temp int default 0;

  declare accname_cursor cursor for
    select distinct accname from tlbbdb.t_char where isvalid = 1;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET cursor_temp = 1;

  set accname_s = NULL;
  set charname_s = NULL;

  /* truncate table tlbb_moneylist; */

  /* start transaction; */

    open accname_cursor;
    REPEAT
      fetch accname_cursor into accname_s;
      select max(level) into maxlevel_i from tlbbdb.t_char where accname = accname_s and isvalid = 1;
      select charname into charname_s from tlbbdb.t_char where accname = accname_s and level = maxlevel_i limit 1;
      select sum(vmoney) into vmoney_i from tlbbdb.t_char where accname = accname_s and isvalid = 1;
      select sum(bankmoney) into bankmoney_i from tlbbdb.t_char where accname = accname_s and isvalid = 1;
      select sum(profit) into shopmoney_i from tlbbdb.t_pshop where ownerguid in (select charguid from tlbbdb.t_char where accname = accname_s and isvalid = 1) and isvalid = 1;
      select (vmoney_i + bankmoney_i + shopmoney_i) into totalmoney_i;
      if totalmoney_i  >= 100000 then
        insert into tlbb_moneylist(accname,charname,level,vmoney,bankmoney,totalmoney) values(accname_s,charname_s,maxlevel_i,vmoney_i,bankmoney_i,totalmoney_i);
      end if;
    UNTIL cursor_temp = 1 END REPEAT;
    close accname_cursor;

  /* commit; */

END //

delimiter ;
