#define SUPPORT_OPENSSL
#include "common.h"

#define BUFLEN 1024
#define KEY_FILE "d:\\pri.key"

void main()
{
	unsigned char   input[BUFLEN] = "This is a test string!",
		output1[BUFLEN] = {0}, 
		output2[BUFLEN] = {0}, 
		output3[BUFLEN] = {0}, 
		output4[BUFLEN] = {0},
		*p = output1;
		
	typedef char* LPCCHAR;
	LPCCHAR pkn = 0,pkd = 0,pkp = 0,pkq = 0,pku = 0,pkdp = 0,pkdq = 0,pke = 0; 
    OpenSSL_add_all_algorithms();
		
	RSA   *key; 
	key   =   RSA_new(); 
	key   =   RSA_generate_key(1024,   65537,   NULL,   NULL); 
	int   len_n = 0, len_e = 0, r= 0; 

	char* modulus = BN_bn2hex(key-> n);
	char* exponent = BN_bn2hex(key-> e);

	 pkn =   BN_bn2hex(key-> n); 
	 pke =   BN_bn2hex(key->e); 
	 pkd   =   BN_bn2hex(key-> d); 
	 pkdp   =   BN_bn2hex(key-> dmp1); 
	 pkdq   =   BN_bn2hex(key-> dmq1); 
	 pkp   =   BN_bn2hex(key-> p); 
	 pkq   =   BN_bn2hex(key-> q); 
	 pku   =   BN_bn2hex(key-> iqmp); 
	 
	 	cout << pkn <<
	endl << pke <<
	endl << pkd <<
	endl << pkdp<<
	endl << pkdq<<
	endl << pkp <<
	endl << pkq <<
	endl << pku << endl << "-------------------------------------\n";

	pkn = "cac1c020bc9f9c322f41b8b68a0a8195322be6b7a0f2035ad5659019787ca38521bbfd416f7797cfb075d2ae2b33a75e856c42974b99cdb8ea608bf0a196e979a8ba7771bd2b829fedfe80f84c78e466a4b7e76d4ad570184b2e7e8b6b5e9032a16851cb32f48687df3a6dd09dcefc2093c7391d265b9946ae657f8754f030d3";
	pke = "010001";
	pkd = "952445be0ee15d14b11c27d1e5e26a85235d959d773eede6cfd7a0528c052a87105466aace626b01f3ac0767e4115fc8b05dfcf1ab439c46abe88ea7574559c0b9999b57a31701054c7f1c8ae32b0b669686ff1a11d001f33749899926e3364de707d9974c35e6586bb5ef369912a4f56aaa9338e5eabab6839fa94673060f61";
	pkdp = "458325be85009066bfcd4c962a517d0dce2f722510b3b9fdefbdbf77f78edc0cbc1b40d6a0447971625ef288a2ad20b9b1e840da9536ef916b78b1a525b32f71";
	pkdq = "149d45155d9983fab515865faead34722c6d4c7c569fb392bed46b4f8f2090dc3cac550cdec17ed2dbc461c590893ddb9279a92346057d3f7738853b9fa26273";
	pkp = "fd9c996d5582a2999b124a4cbe396cb6fa87ef8853ec996d51d03f04222141e850f2cd6421f679d1e86ec6931f1445793f25d1f375aafc92092dfa2048dbc651";
	pkq = "ccaa8d30ee3bb53ca852a986300be92c0d2a58b81a37da8dcd7932ff5b91b41891d7a7ef156210397f726d84af674aafd9bb2f8b4fa6270d3e2ac15f660927e3";
	pku = "3b39ecde9ebf6c7cb588a1132017a8ede10cf2f70a722386c978e0e6b7d5f74a6816582ee29ea154ad71058650c4a6e8d93b1d89cf088603376ab8c150e2515b"; 
	
	cout << pkn <<
	endl << pke <<
	endl << pkd <<
	endl << pkdp<<
	endl << pkdq<<
	endl << pkp <<
	endl << pkq <<
	endl << pku << endl << "-------------------------------------\n";


	//encrypt 

	RSA   *pkey; 
	pkey   =   RSA_new(); 
	pkey-> dmq1   =   BN_new(); 
	pkey-> dmp1   =   BN_new(); 
	pkey-> p   =   BN_new(); 
	pkey-> q   =   BN_new(); 
	pkey-> iqmp   =   BN_new(); 
	pkey-> e   =   BN_new(); 
	pkey-> n   =   BN_new(); 
	pkey-> d   =   BN_new(); 
	
	//~ r   =   BN_hex2bn(&pkey-> e,   pke); 
	//~ r   =   BN_hex2bn(&pkey-> n,   pkn); 
	//~ r   =   BN_hex2bn(&pkey-> d,   pkd); 
	//~ r   =   BN_hex2bn(&pkey-> dmp1,   pkdp); 
	//~ r   =   BN_hex2bn(&pkey-> dmq1,   pkdq); 
	//~ r   =   BN_hex2bn(&pkey-> p,   pkp); 
	//~ r   =   BN_hex2bn(&pkey-> q,   pkq); 
	//~ r   =   BN_hex2bn(&pkey-> iqmp,   pku); 


	char* hex = // "1debab2853009f4a64e3820af9b5011ce447b0b4ca4e06830bdd9ab49d24990a8d66e36a67d168433645e2141b9092e302722db6e210839e7020778012c5f667abd3cc8cb695965467157d1af17a1a87eeedf25802f8b87245de4f6f645f6404686e50baab4d6ba340892595d21a92d44833fa1ad223d1d52fd74eea100f6d23";
//"83f5d0291990e46915356c2c2bb20fb91b2ff3b9a5cf067770b19c6383970fe4ad4598ddbe2941af8f49fb3b5afe44bf36d57d3c26ccafd119e9e5ad643fd4a4f196a6e8cf8dfa38a7de161d1cdd04d781fa4f25800f3d42ad598813ca19c0d1d56ddd5d4a590caf73ce850f077b7fe16da97bee3003c4f6cd7980310e8ded9a";
"C137D7F3ECFBE27CDE208B21822CB633229058DF77A65CBE84D1451031E0736E54574E3674000A0D7F7E3870CF418B7BA038EC799A3F15C913021B12169C24527240EEC66C0BA542DF36AEAB411D0EF1B8029999053F6A5FFA04A6153A8764D6012917452184AD4E4D2F740005D9A931B1FF85EC0EA4A910BB2AC4FCF08C8093";
	BIGNUM* bn = BN_new();
	r = BN_hex2bn(&bn, hex);
	char* tmp = BN_bn2dec(bn);
	cout<< endl << tmp<< endl;
	
	hex = "61df8e498bbbc1499c52c07b2dbbe3801944ded5a1d47e02f41b85931a23a54af32d9e57e4949b05cbc5378f37743557936c610138c50fc6770471517b924e45d32be2aca4c9614fc66fd927b63e9ba3d2e3a8d58be1f19eddfd0229a8cbc8f86ac35397c74b9a81bf8927f66e3fd3be53d6f80a15e45af60ca7e21790670402";
	hex = "3644456bc7dd199ffe1457ad522381e0c09ff75081eded6d485543df469eac622d33c0f3fff6dd782a756a11faa628e778ec20c1a29ce0c5bfa7cfbb2662741630f0887cc47ce462fb4f9826aca539d2b94425c6d6bcf730bb9652c5e6679dfa12934e87edec448a10f6878600188b5110c9ad2a427067e993807145c19542fe";
	BIGNUM* bn2 = BN_new();
	r = BN_hex2bn(&bn, hex);
	r = BN_bn2bin(bn, output1);
	{
		ofstream f("d:\\enc.bin", ios::binary);
		f.write((const char*)output1, 128);
		f.close();
	}
	return;

	hex = "104551245207708733804443243686142399190035872724676220957767593810710888828594328202014687287253036812883284083534341059998159906766691051098362485201964980471625752357069445183671736157729988610967924750562633297192472247326960391762327350616211239074133921832221571818981023807964776443542146023519121863793";
	
	r   =   BN_dec2bn(&pkey->n,   hex); 
	r   =   BN_dec2bn(&pkey-> e,   "3"); 

	

	//~ FILE *f = NULL; 
	//~ f = fopen(KEY_FILE, "wb"); 
	//~ if(f == NULL) 
	//~ { 
	  //~ return; 
	//~ } 
    //~ static char *passphrase = "test passphrase";
	//~ cout << "#############################\n" << PEM_write_RSAPrivateKey(f, pkey, EVP_des_ede3_cbc(), (unsigned char *)passphrase,strlen(passphrase), 0, 0) << endl; 
	//~ fclose(f); 
		

// 	long len1   =   RSA_public_encrypt(strlen((char*)input),   input,   output1,   key,   RSA_PKCS1_PADDING);   
	long len2   =   RSA_public_encrypt(strlen((char*)input),   input,   output2,   pkey,   RSA_PKCS1_PADDING); 
	ofstream f("d:\\enc.bin", ios::binary);
	f.write((const char*)output2, len2);
	f.close();
	return;

//	RSA_private_decrypt(r, output1, output3, pkey, RSA_PKCS1_PADDING);
	int len = RSA_public_decrypt(r, output1, output3, pkey, RSA_NO_PADDING);
	len = RSA_padding_check_PKCS1_type_2(output1, len, output3 + 1, len - 1, len);
	string str((char*)output1, len);
}