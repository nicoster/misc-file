NameSpace = "http://schemas.microsoft.com/cdo/configuration/"
set Email = CreateObject("CDO.Message")
Email.From =  "nickx@sz.webex.com"
Email.To =  "nickx@sz.webex.com"
Email.Subject = "sendmail.vbs"
Email.Textbody = "OK!"
with Email.Configuration.Fields
.Item(NameSpace&"sendusing") = 2
.Item(NameSpace&"smtpserver") = "smtp.21cn.com" 
.Item(NameSpace&"smtpserverport") = 25
.Item(NameSpace&"smtpauthenticate") = 1
.Item(NameSpace&"sendusername") = "zzzevazzz"
.Item(NameSpace&"sendpassword") = "ph4nt0m!"
.Update
end with
Email.Send