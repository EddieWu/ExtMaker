#ifndef YHADIRERROR_H
#define YHADIRERROR_H
typedef enum RetCodetag
{
	Result_OK=0,					//0		SUCCESS
	Result_ERROR,					//1		һ�����
	ERROR_UNKNOWNSTATIONNAME,		//2		δ֪����վ����
	ERROR_CURRENTOUTOFRANGE,		//3		����������Χ
	ERROR_UNEXPECTEDCHARGER,		//4		��Ӧ�еĳ����
	ERROR_FINDNOCHARGER,			//5		û���ֳ����
	ERROR_TEMPRETUREADCOUTOFRANGE,	//6		�¶ȳ�����Χ
	ERROR_FREQERROR_TOOLARGE,		//7		AFCʱƵ�����̫��
	ERROR_FREQERROR_TOONEAR,		//8     AFCʱ����ADCֵ��Ӧ��Ƶ�����̫�ӽ�
	ERROR_FREQERROR_OUTOFRANGE,		//9		AFCʱƵ��������Χ
	ERROR_TXPOWEROUTOFRANGE,		//10	���书�ʳ�����Χ
	ERROR_GSYS_SIZE,				//11	BRCM AGCʱindex����GSYS_SIZE�ķ�Χ
	ERROR_READGSYS,					//12	BRCM AGCʱ��ȡGSYSʧ��
	ERROR_FILENOTEXISTED,			//13	�ļ�������
	ERROR_FILEOPENFAIL,				//14	���ļ�ʧ��
	ERROR_FILETOOSMALL,				//15	�ļ����Ȳ���
	ERROR_FILEREADFAIL,				//16	��ȡ�ļ�ʧ��
	ERROR_NOTACHIEVEEXPPOWER,		//17	�޷�У׼����������
	ERROR_NOSYNC,					//18	�ֻ�ע������ʧ��
	ERROR_NOCEST,					//19	���۲��ǽ���ͨ��ʧ��
	ERROR_BASECALLFAIL,				//20	�۲��Ƿ������ʧ��
	ERROR_BASEENDCALLFAIL,			//21	�۲��ǽ���ͨ��ʧ��
	ERROR_ENDCALLFAIL,				//22	����ͨ��ʧ��
	ERROR_PEAKPOWEROUTOFRANGE,		//23	��ֵ���ʳ�����Χ
	ERROR_READPEAKPOWERERROR,		//24	�۲��Ƕ�ȡ��ֵ����ʧ��
	ERROR_FREQEEEROROUTOFRANGE,		//25	Ƶ��������Χ
	ERROR_READFREQERRORFAIL,		//26	�۲��Ƕ�ȡƵ�����ʧ��
	ERROR_PEAKPHASEERROR,			//27	��ֵ��λ������Χ
	ERROR_READPEAKPHASEERROR,		//28	�۲��Ƕ�ȡ��ֵ��λ���ʧ��
	ERROR_RMSPHASEERROR,			//29	��������λ������Χ
	ERROR_READRMSPHASEERROR,		//30	�۲��Ƕ�ȡ��������λ���ʧ��
	ERROR_POSFLATTNESS,				//31	��ƽ̹�ȳ�����Χ
	ERROR_READPOSFLATTNESS,			//32	�۲��Ƕ�ȡ��ƽ̹��ʧ��
	ERROR_BANDHANDOVER,				//33	Bandhandoverʧ��
	ERROR_NEGFLATTNESS,				//34	��ƽ̹�ȳ�����Χ
	ERROR_READNEGFLATTNESS,			//35	�۲��Ƕ�ȡ��ƽ̹��ʧ��
	ERROR_MODSPECTRUM,				//36	����Ƶ�׳�����Χ
	ERROR_READMODSPECTRUM,			//37	�۲��Ƕ�ȡ����Ƶ��ʧ��
	ERROR_SWTSPECTRUM,				//38	����Ƶ�׳�����Χ
	ERROR_READSWTSPECTRUM,			//39	�۲��Ƕ�ȡ����Ƶ��ʧ��
	ERROR_TIMEMASK,					//40	����ʱ����糬����Χ
	ERROR_READTIMEMASK,				//41	�۲��Ƕ�ȡ����ʱ�����ʧ��
	ERROR_RXLEVEL,					//42	���յ�ƽ������Χ
	ERROR_READRXLEVEL,				//43	�۲��Ƕ�ȡ���յ�ƽʧ��
	ERROR_RXQUALITY,				//44	��������������Χ
	ERROR_READRXQUALITY,			//45	�۲��Ƕ�ȡ��������ʧ��
	ERROR_RBERII,					//46	�����ʳ�����Χ
	ERROR_READRBERII,				//47	�۲��Ƕ�ȡ������ʧ��
	ERROR_CRCOUTOFRANGE,			//48	ѭ������У�鳬����Χ
	ERROR_READCRCOUTOFRANGE,		//49	�۲��ǲ���CRCʧ��
	ERROR_MOBNORESPONSE,			//50	�ֻ�û����Ӧ
	ERROR_MSGLENGTH,				//51	TAT��Ϣ���ȴ���
	ERROR_RETMSGSTRUCT,				//52	�ֻ����ص���Ϣ�ṹ����
	ERROR_NOATRET,					//53	�ֻ���ATָ������Ӧ
	ERROR_BUFFERISNULL,				//54	�������ǿյ�
	ERROR_STOREBTMACFAIL,			//55	�洢����MAC��ַʧ��
	ERROR_BRCMON2PC,				//56	Intel��BRCM�˿�ʧ��
	ERROR_ENTERCALMODEFAIL,			//57	����У׼ģʽʧ��
	ERROR_GETRXLEVELFROMMOBILE,		//58	���ֻ���ȡ���յ�ƽʧ��
	ERROR_DOWNLOAD2PC,				//59	��BRCM�л�������ģʽʧ��
	ERROR_PRESSKEY,					//60	ģ�ⰴ��ʧ��
	ERROR_STOREHWVER,				//61	�洢Ӳ���汾��ʧ��
	ERROR_STORESTATIONFLAG,			//62	�洢����վ��Ϣʧ��
	ERROR_STORESN,					//63	�洢�ֻ����к�ʧ��
	ERROR_STOREPRDSN,				//64	�洢��Ʒ���к�
	ERROR_OPENCOMFAIL,				//65	�򿪴���ʧ��
	ERROR_GETCOMSTATEFAIL,			//66	��ȡ����״̬ʧ��
	ERROR_SETCOMSTATEFAIL,			//67	���ô���״̬ʧ��
	ERROR_SETCOMTIMEOUTFAIL,		//68	���ô��ڳ�ʱ״̬ʧ��
	ERROR_SETCOMMASKFAIL,			//69	����COMMASKʧ��
	ERROR_SETUPCOMFAIL,				//70	SetupComʧ��
	ERROR_PURGECOMFAIL,				//71	PurgeComʧ��
	ERROR_COMNOTOPEN,				//72	����δ��
	ERROR_SERIALPURGE,				//73	PurgeComʧ��
	ERROR_CLEARCOMERRORFAIL,		//74	ClearComErrorʧ��
	ERROR_READCOMFAIL,				//75	��ȡ����ʧ��
	ERROR_READNOCHAR,				//76	û�дӴ��ڶ���ֵ
	ERROR_SERIALPORTWRITE,			//77	д����ʧ��
	ERROR_SERIALWRITEDATA,			//78	δ���򴮿�д��ָ����������
	ERROR_GETNUMFAIL,				//79	�Ӵ��ڽ��յ��������л�ȡ����ʧ��
	ERROR_DIOEXCEPTION,				//80	DIO�����쳣
	ERROR_DIOINITFAIL,				//81	DIO��ʼ��ʧ��
	ERROR_GENSIMLOCKIMGFAIL,		//82	����SimLockImageʧ��
	ERROR_GENBOOTLOADERIMGFAIL,		//83	����BootloaderImageʧ��
	ERROR_NOTREADENOUGHDATAFROMFILE,//84	δ�ܴ��ļ������㹻����
	ERROR_SPEEDREQBYTE,				//85	û���յ������ٶ�����
	ERROR_SPEEDCHGCONF,				//86	û���յ������ٶ�ȷ��
	ERROR_ADDRESSWRONG,				//87	��ַ����
	ERROR_IMGTOOLARGE,				//88	Image�ļ�̫��
	ERROR_DOWNLOADFAIL,				//89	����ʧ��
	ERROR_UNEXPECTEDCMDRECEIVED,	//90	���յ�δ֪������
	ERROR_FOUNDNOTATMSGHEAD,		//91	û���յ�TAT��Ϣͷ
	ERROR_CAPTURENOTATMSG,			//92	û���յ�TAT��Ϣ
	ERROR_SETRTCFAIL,				//93	����RTCʧ��
	ERROR_DOUBLECHECKRTCFAIL,		//94	����У��RTCʧ��
	ERROR_CHECKRTCFAIL,				//95	У��RTCʧ��
	ERROR_SETCHARGEMODEFAIL,		//96	�����ֻ�������ģʽʧ��
	ERROR_READCODECREGISTER,		//97	��ȡCODEC�Ĵ���ʧ��
	ERROR_WRITECODECREGISTER,		//98	дCODEC�Ĵ���ʧ��
	ERROR_CHECKDATA,				//99	У���DOC Memory����������ʧ��
	ERROR_SDRAMCHECKFAIL,			//100	SDRAM����ʧ��
	ERROR_STARTBTFAIL,				//101	��������ʧ��
	ERROR_RESETBTFAIL,				//102	��������ʧ��
	ERROR_LASTSTATIONNOTPASS,		//103	��һվ����δͨ��
	ERROR_SNLENGTH,					//104	SN���ȴ���
	ERROR_INVALIDCHARINSN,			//105	SN������Ч�ַ�
	ERROR_COPYFILE,					//106	�����ļ�����
	ERROR_WRITEINI,					//107	дINI�ļ�����

	ERROR_GETAFCOFFSET,				//108	���ֻ���ȡƵ�����ʧ��
	ERROR_ZEROAFCOFFSET,			//109	���ֻ���ȡƵ�����ʧ��
	ERROR_AFCOFFSETOUTOFRANGE,		//110	AFCʱƵ��������Χ
	ERROR_NORMINALAFCVALOUTOFRANE,	//111	AFC DAC������Χ
	ERROR_SLOPEPPBOUTOFRANGE,		//112	AFCֱ��б�ʳ�����Χ
	ERROR_READRSSI,					//113	��ȡRSSI����
	ERROR_RSSILEVELTOOLOW,			//114	RSSI̫С
	ERROR_AGC_NORACHIEVENPRMALLEVEL,//115	�޷�У׼��������AGC Level
	ERROR_RSSIOUTOFRANGE,			//116	RSSI������Χ
	ERROR_ILLEGLEPHONENUMBER,		//117	�Ƿ��ĵ绰����
	ERROR_COM_SENDSETUP,			//118	�ֻ�ͬ��ʧ��
	ERROR_EXIT_MODE,				//119	�˳�У׼ģʽʧ��
	ERROR_PREPARE_PHASE,			//120	ԤУ׼ʧ��
	ERROR_READ_BATTVOLT,			//121	���ֻ���ȡ��ص�ѹʧ��
	ERROR_SET_LCD_CONTRAST,			//122	����LCD�Աȶ�ʧ��
	ERROR_CALVALUE,					//123	����У׼����ʧ��
	ERROR_LOAD_CALPARAM,			//124	��ȡCalParamʧ��
	ERROR_STORE_CALPARAM,			//125	�洢CalParamʧ��
	ERROR_WRITE_CALPARAM,			//126	��YHT��ʽ�洢CalParamʧ��
	ERROR_DUMPMEMORY,				//127	DUMPMEMORYʧ��
	ERROR_SET_AFCDAC,				//128	Set AFC DACʧ��
	ERROR_STORE_AFC,				//129	�洢AFC���ʧ��
	ERROR_STORE_DCOFFSET,			//130	�洢DC Offsetʧ��
	ERROR_STORE_AGC,				//131	�洢AGC����ʧ��
	ERROR_STORE_RSSI,				//132	�洢RSSIʧ��
	ERROR_STORE_PWRRAMP,			//133	�洢APCʧ��
	ERROR_STORE_TXFREQCOMP,			//134	�洢Ƶ�ʲ���ʧ��
	ERROR_STORE_BATTADC,			//135	�洢Battery DACʧ��
	ERROR_SET_GAIN,					//136	SetGainProgramDataʧ��
	ERROR_SET_BANDMODE,				//137	����Ƶ��ģʽʧ��
	ERROR_SET_RECVTRANSBURST,		//138	����RecvTransBurstʧ��
	ERROR_SET_BURSTDATA,			//139	����BurstDataʧ��
	ERROR_SET_RAMP_SCALE_FACTOR,	//140	����ScaleFactorʧ��
	ERROR_READ_RTCSTAT,				//141	��ȡRTCʧ��
	ERROR_SET_RXCONTROL,			//142	����RxControlʧ��
	ERROR_WRITE_SIMINFO,			//143	дSIM����Ϣʧ��
	ERROR_PROTOCOLSTATE,			//144	����Э��ջʧ��
	ERROR_AFM_SEND_BANDMODE,		//145	����Ƶ��ģʽʧ��
	ERROR_SETBANDMODE_CALLTEST,		//146	����Ƶ��ģʽ
	ERROR_SIMLOCK,					//147	����ʧ��
	ERROR_GET_AFC,					//148	��ȡAFC����
	ERROR_GET_AGC,					//149	��ȡAGC����
	ERROR_GET_RSSI,					//150	��ȡRSSI����
	ERROR_GET_PWRRAMP,				//151	��ȡAPC����
	ERROR_VIBRATORTESTFAIL,			//152	�𶯲���ʧ��
	ERROR_LEDTESTFAIL,				//153	LED����ʧ��
	ERROR_LOADHWVER,				//154	��ȡӲ���汾�Ŵ���
	ERROR_LOADSN,					//155	��ȡ���кŴ���
	ERROR_GET_BOARDFLAG,			//156	��ȡ����վ��Ϣ����	
	ERROR_STORE_VCXO,				//157	�洢VCXO����
	ERROR_VCXO_MEAS,				//158	VCXOУ׼����
	ERROR_TXCURRENTFAIL,			//159	�������������Χ
	ERROR_LCDBKLIGHTFAIL,			//160	LCD�������ʧ��
	ERROR_READGPIOSTATUS,			//161	��ȡGPIO״̬ʧ��
	ERROR_INVALIDSDCARD,			//162	��ȡSD��״̬ʧ��
	ERROR_STOREPRODUCTSN,			//163	�洢��ƷSNʧ��
	ERROR_LOADPRODUCTSN,			//164	��ȡ��ƷSNʧ��
	ERROR_STORECUSTOMERINFO,		//165	�洢�ͻ���Ϣʧ��
	ERROR_LOADCUSTOMERINFO,			//166	��ȡ�ͻ���Ϣʧ��
	ERROR_SETTIMINGADV,				//167	����ʱ����ǰ��ʧ��
	ERROR_FER,						//168	֡�����ʳ�����Χ
	ERROR_READFER,					//169	��ȡ֡������ʧ��
	ERROR_BER,						//170	����BERʧ��
	ERROR_READBER,					//171	��ȡBERʧ��
	ERROR_LOADSWVER,				//172	��ȡ����汾�Ŵ���
	ERROR_STOREFLAG,				//173	��־λ�洢����
	ERROR_INVALIDIMGFILE,			//174	IMG�ļ�����Ч
	ERROR_WRONGSTATIONFLAG,			//175	����վ���Ʊ�־����
	ERROR_INVALIDCHARINHWVER,		//176	Ӳ���汾��������Ч�ַ�
	ERROR_INVALIDCHARINSWVER,		//177	����汾��������Ч�ַ�
	ERROR_LOAD_TXFREQCOMP,          //178   ��ȡƵ�ʲ�������
	ERROR_SIM_UNLOCK,				//179   ��������
	ERROR_SIM_USER_CANCEL,          //180   ������ͻ������ȡ��
	ERROR_SIM_PIN_ERROR,			//181   PIN����֤����			
	ERROR_SIM_NOTLOCK,				//182   ��û�м���
	ERROR_LOADBTMACFAIL,			//183	��ȡ����MAC��ַʧ��//melancholic 20061121 a
	ERROR_RESTARTMOBFAIL,			//184	�����ֻ�ʧ��
	ERROR_UNCOMPATIBLEDRIVERLIB,	//185	���Ժ������뵱ǰϵͳ������
	ERROR_SETLOGSTATE,				//186	����Log��Ϣ״̬ʧ��
	ERROR_LOADGPIBDRIVERDLL,		//187	װGPIBʧ��
	ERROR_WRONGGPIBCARDTYPE,		//188	�����GPIB�豸����
	ERROR_GPIBSETTING,				//189	GPIB��������ȷʧ��
	ERROR_GETGPIBDEVICE,			//190	�Զ���ȡGPIB�豸���ʹ���
	ERROR_GETDLLFUNCTION,			//191	װ��DLLʧ��
	ERROR_GETGPIBTYPE,				//192	��ȡGPIB�豸����
	ERROR_OPENGPIBDEV,				//193	��GPIB�豸ʧ��
	ERROR_READTIMINGADV,			//194	��ȡʱ����ǰ��ʧ��
	ERROR_READBERA,					//195	��ȡberaʧ��
	ERROR_READBERB,					//196	��ȡberbʧ��
	ERROR_READCRC,					//197	��ȡCRCʧ��
	ERROR_READRBERA,				//198	��ȡRberaʧ��
	ERROR_READRBERB,				//199	��ȡRberbʧ��
	ERROR_READRCRC,					//200	��ȡRCRCʧ��
	ERROR_NO_OBJECT,				//201	û�гɹ���������
	ERROR_LOADVISADRIVERDLL,		//202	װVISAʧ��
	ERROR_WRONGPLATFORMTYPE,		//203	�����ƽ̨
	ERROR_OPENPLATFORM,				//204	�򿪵�ƽ̨ʧ��
	ERROR_NORFDEFAULTFILE,			//205	��Ƶ�����ļ�default�ļ���ʧ
	ERROR_NORFCONFIGFILE,			//206	��Ƶ�����ļ�CONFIG�ļ���ʧ
	ERROR_SWITCHDEBUG,				//207	��debugģʽʧ��
	ERROR_CRYSTALAFCFAIL,			//208	Crystal AFC ʧ��
	ERROR_GETDEVVOLTAGE,			//209	��ȡ�豸��ѹʧ��
	ERROR_SETDEVVOLTAGE,			//210	�����豸��ѹʧ��
	ERROR_GETDEVCURRENT,			//211	��ȡ�豸����ʧ��
	ERROR_SETDEVCURRENT,			//212	�����豸����ʧ��
	ERROR_BATT_ADC_Slop_Offset_FAIL,//213	ADC SLOPE �� Offset����ʧ��
	ERROR_CHAR_ADC_Slop_Offset_FAIL,//214	ADC SLOPE �� Offset����ʧ��
	ERROR_BATT_CHAN_Slop_FAIL,		//215	Check Battey Channel Slop Failed
	ERROR_BATT_CHAN_Offset_FAIL,	//216	Check Battey Channel Offset Failed
	ERROR_ADC_Cal_Curr_FAIL,		//217	ADC Calibration Curr difference
	ERROR_ADC_Cal_Volt_FAIL,		//218	ADC Calibration voltage difference
	ERROR_AGC_Cal,					//219	AGC У׼ʧ��
	ERROR_AGC_Check,				//220	AGC У׼����ʧ��
	ERROR_GET_IQImbalance,			//221	IQImbalance��ȡʧ��
	ERROR_GET_OriginalOffset,		//222	OriginalOffset��ȡʧ��
	ERROR_APC_Check_Fail,			//223	APC ���ʧ��
	ERROR_TXIQ_EDGE_FAIL,			//224	TXIQ EDGE У׼ʧ��
	ERROR_GET_EDGEIQImbalance,		//225	edge IQImbalance��ȡʧ��
	ERROR_GET_EDGEOffset,			//226	edge OriginalOffset��ȡʧ��
	ERROR_APC_EDGE_Check_Fail,		//227	edge APC check
	ERROR_APC_SWING,				//228	�������Ҳ����޷�У׼��
	ERROR_READ_EDGEOVER,			//229	�޷���ȡEdge Overview
	ERROR_READ_EDGEBER,				//230	�޷���ȡEDGE��BER
	ERROR_SET_DLULPARA,				//231	���������еĲ�������
	ERROR_READ_IMEI,				//232	��ȡIMEI����
	ERROR_WRITE_IMEI,				//233	д��IMEI����
	ERROR_NO_APC_METHOD,			//234	û��APC���У׼�㷨
	ERROR_AFC_CW_FAIL,				//235	AFC��CWУ׼�㷨���ִ���
	ERROR_EXIST_IMEI,				//236	�Ѵ���IMEI���������ظ�д��
	ERROR_WIFIMACILLEGAL,			//237	д��WIFI��ַʧ��
}RetCode;

#define ASSERTRES(res) if((res)!=Result_OK){return (res);}
#endif
