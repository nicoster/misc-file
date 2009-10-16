String.prototype.trim = function()
{
    return this.replace(/(^[\\s]*)|([\\s]*$)/g, "");
}
String.prototype.lTrim = function()
{
    return this.replace(/(^[\\s]*)/g, "");
}
String.prototype.rTrim = function()
{
    return this.replace(/([\\s]*$)/g, "");
} 

function toString2(array)
{
    var str = "";
    var i = 0;
    var len = array.length;
    for (i= 0; i < len; ++i)
      str += array[i] + " ";
      
    return str;
}

function IniStruct()
{
  this.Name = new String();
  this.Attribute = new Object();
  this.setName = function(Name)
  {
    Name = Name.toString();
    var re = /^[^\s]+$/;
    if(!re.test(Name))
    {
      return false;
    }
    else
    {
      this.Name = Name;
      return true;
    }
  }
  this.setAttribute = function(AttributeName,AttributeValue)
  {
    AttributeName = AttributeName.toString();
    AttributeValue = AttributeValue.toString();
 //   alert('1.' +AttributeValue);
    var reforName = /^\w+$/i;
    var reforValue = /^[^\s]*$/;
 /*   if(!reforName.test(AttributeName) || !reforValue.test(AttributeValue))
    {
      return false;
    }
    else*/
    {
      this.Attribute[AttributeName] = AttributeValue;
      return true;
    }
  }
  this.getAttribute = function(AttributeName)
  {
    var reforName = /^\w+$/i;
    if(!reforName.test(AttributeName))
    {
      return false;
    }
    else
    {
      return this.Attribute[AttributeName];
    }
  }
  this.toString = function()
  {
    var Str = new String();
    Str += "[" + this.Name + "]\n";
    for(var p in this.Attribute)
    {
      Str += p + "=" + this.Attribute[p] + "\n";
    }
    return Str;
  }
  this.getArr = function()
  {
    var Arr = new Array();
    Arr[0] = "[" + this.Name + "]";
    var i = 1;
    for(var p in this.Attribute)
    {
      Arr[i++] = p + "=" + this.Attribute[p];
    }
    return Arr;
  }
}

function IniCtrl()
{
  this.FilePath = new String();
  this.fso = new ActiveXObject("Scripting.FileSystemObject");
  this.file = null;
  this.IsOpen = false;
  this.IniStruct = null;
  this.Struct = null;
  this.FilePath = null;
  this.Close = function()
  {
    if(this.file != null)
    {
      this.file.Close();
    }
    this.IniStruct = null;
    this.file = null;
     this.FilePath = null;
    this.IsOpen = false;
  }
  this.Open = function(FilePath)
  {
    FilePath = FilePath.toString();
    var Re = /^.+\.ini$/i;
    if(!Re.test(FilePath))
    {
      alert("文件名出错，后缀名应该为.ini");
      this.Close();
      return false;
    }
    else
    {
      if(!this.fso.FileExists(FilePath))
      {
        alert("文件不存在");
        this.Close();
        return false;
      }
      else
      {
        this.Close();
        this.file = this.fso.OpenTextFile(FilePath,1,false);
        this.IsOpen = true;
        if(!this.Init())
        {
          return false;
        }
        this.FilePath = FilePath;
        return true;
      }
    }
  }
  this.Create = function(FilePath)
  {
    FilePath = FilePath.toString();
    var Re = /^.+\.ini$/i;
    if(!Re.test(FilePath))
    {
      alert("文件名出错，后缀名应该为.ini");
      this.Close();
      return false;
    }
    else
    {
      if(this.fso.FileExists(FilePath))
      {
        alert("文件已经存在");
        this.Close();
        return false;
      }
      else
      {
        try
        {
          this.Close();
          this.file = this.fso.CreateTextFile(FilePath, 2,false);
          this.IsOpen = true;
          this.FilePath = FilePath;
          return true;
        }
        catch(ex)
        {
          alert("无法新建文件，可能磁盘已经满或者文件名格式不正确");          
          this.Close();
          return false;
        }
      }
    }
  }
  this.Init = function()
  {
    if(!this.IsOpen)
    {
      alert("文件还未打开");
      return false;
    }
    else
    {
      var tmpStr = new Array();      
      while(!this.file.AtEndOfStream)
      {
        tmpStr[tmpStr.length] = this.file.ReadLine();
      }
      var tmpStruct = null;
      this.IniStruct = new Array();
      var At = 0;
      var reForSet = /^\[([^\s]+)\]$/i;
      var reForAtt = /^(\w+)=(.*)/i;
      var Name = new String();
      var i = 0;
      var AttName = null;
      var AttValue = null;
      while(i < tmpStr.length)
      {
        if(reForSet.test(tmpStr[i]))
        {
          At = this.IniStruct.length;
          this.IniStruct[At] = new IniStruct();
          tmpStruct = this.IniStruct[At];
          Name = tmpStr[i].replace(reForSet,"$1");
          if(!tmpStruct.setName(Name))
          {
            this.IniStruct.length = At;
            tmpStruct = (At == 0) ? null : this.IniStruct[At - 1];
          }
        }
        
        if(reForAtt.test(tmpStr[i]) && (tmpStruct != null))
        {
          AttName = tmpStr[i].replace(reForAtt,"$1");
          AttValue = tmpStr[i].replace(reForAtt,"$2");
//          alert(AttName + AttValue);
          tmpStruct.setAttribute(AttName,AttValue);
        }
        i++;
      }
      
      return true;
    }
  }
  this.select = function(Name)
  {
    if(this.IniStruct == null)
    {
      return false;
    }
    else
    {
      for(var i = 0; i < this.IniStruct.length; i++)
      {
        if(this.IniStruct[i].Name == Name)
        {
          this.Struct = this.IniStruct[i];
          return true;
        }
      }
      this.Struct = null;
      return false;
    }
  }
  this.setAttribute = function(AttributeName,AttributeValue)
  {
    if(this.Struct == null)
    {
      return false;
    }
    else
    {
      return this.Struct.setAttribute(AttributeName,AttributeValue);
    }
  }
  this.getAttribute = function(AttributeName)
  {
    if(this.Struct == null)
    {
      return false;
    }
    else
    {
      return this.Struct.getAttribute(AttributeName);
    }
  }
  this.save = function()
  {
    if(!this.IsOpen)
    {
      alert("文件还未打开");
      return false;
    }
    else
    {
      try
      {
        var tmpfso = new ActiveXObject("Scripting.FileSystemObject");
        var tmpName = tmpfso.GetTempName();
        var f = tmpfso.CreateTextFile(tmpName,2,false);
        var FilePath = this.FilePath;
        var Arr = null;
        for(var i = 0; i < this.IniStruct.length; i++)
        {
          Arr = this.IniStruct[i].getArr();
          for(var t = 0; t < Arr.length; t++)
          {
            f.WriteLine(Arr[t]);
          }
        }
        this.Close();
        tmpfso.DeleteFile(FilePath);
        tmpfso.CopyFile(tmpName,FilePath);
        f.Close();
        tmpfso.DeleteFile(tmpName);
        this.Open(FilePath,1);
        return true;
      }
      catch(ex)
      {
        alert("无法保存");
        return false;
      }
    }
  }
  this.addSetting = function(SetName)
  {
    if(!this.select(SetName))
    {
      var tmpStruct = new IniStruct();
      if(!tmpStruct.setName(SetName))
      {
        return false;
      }
      else
      {
        if(this.IniStruct == null)
        {
          this.IniStruct = new Array();
        }
        this.IniStruct[this.IniStruct.length] = tmpStruct;
        return true;
      }
    }
  }
}
