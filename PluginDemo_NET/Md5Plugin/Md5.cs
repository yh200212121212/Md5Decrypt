using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using DotNet4.Utilities;
//不能擅自修改
namespace Md5Plugin
{
    //不能擅自修改
    public class Md5
    {
        
        /// <summary>
        /// MD5解密函数
        /// </summary>
        /// <param name="md5">md5密文</param>
        /// <returns>md5明文</returns>
        public static string Md5Text(string md5)
        {

            HttpHelper http = new HttpHelper();
            HttpItem item = new HttpItem()
            {
                URL = "http://md5.syue.com/ShowMD5Info.asp?GetType=ShowInfo&no-cache=0.17596478294581175&md5_str=" + md5 + "&_=",//URL     必需项    
                //Encoding = System.Text.Encoding.GetEncoding("utf-8"),//URL     可选项 默认为自动识别  
                Method = "get",//URL     可选项 默认为Get   
                IsToLower = false,//得到的HTML代码是否转成小写     可选项默认转小写   
                Cookie = "",//字符串Cookie     可选项   
                Referer = "http://www.test404.com/",//来源URL     可选项   
                Postdata = "",//Post数据     可选项GET时不需要写   
                Timeout = 10000,//连接超时时间     可选项默认为100000    
                ReadWriteTimeout = 10000,//写入Post数据超时时间     可选项默认为30000   
                UserAgent = "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)",//用户的浏览器类型，版本，操作系统     可选项有默认值   
                ContentType = "text/html",//返回类型    可选项有默认值   
                Allowautoredirect = false,//是否根据301跳转     可选项    
                ResultType = ResultType.String
            };
            HttpResult result = http.GetHtml(item);
            string html = GetStrMiddle(result.Html, "color:#FF0000;line-height:25px\">", "</span>");
            return html.Trim();
        }
        //作者
        public static string Author()
        {
            return "Test404";
        }
        //网址
        public static string WebSite()
        {
            return "http://md5.syue.com/";
        }

        
        //Url解码,encoding默认为utf8编码
        private static string UrlDecode(string str, Encoding encoding = null)
        {
            if (encoding == null)
            {
                return System.Web.HttpUtility.UrlDecode(str, Encoding.UTF8);
            }
            else
            {
                return System.Web.HttpUtility.UrlDecode(str, encoding);
            }
        }

        //Url编码,encoding默认为utf8编码
        private static string UrlEncode(string str, Encoding encoding = null)
        {
            if (encoding == null)
            {
                return System.Web.HttpUtility.UrlEncode(str, Encoding.UTF8);
            }
            else
            {
                return System.Web.HttpUtility.UrlEncode(str, encoding);
            }
        }

        // 取文本左边
        private static string GetStrLeft(string str, string left, int length = 0)
        {
            var pos = str.IndexOf(left, StringComparison.Ordinal);
            if (pos < 0) return "";
            string result = "";
            if (length == 0)
            {
                result = str.Substring(0, pos);
            }
            else
            {
                result = str.Substring(length, pos);
            }
            return result;
        }

        // 取文本右边
        private static string GetStrRight(string str, string right, int length = 0)
        {
            int pos = str.IndexOf(right, StringComparison.Ordinal);
            if (pos < 0) return "";
            int len = str.Length;
            if (len - pos - right.Length <= 0) return "";
            string result = "";
            if (length == 0)
            {
                result = str.Substring(pos + right.Length, len - (pos + right.Length));
            }
            else
            {
                result = str.Substring(pos + right.Length, length);
            }
            return result;
        }

        // 取文本中间
        private static string GetStrMiddle(string allStr, string firstStr, string lastStr)
        {
            //取出前面的位置
            int index1 = allStr.IndexOf(firstStr);
            //取出后面的位置
            int index2 = allStr.IndexOf(lastStr, index1 + firstStr.Length);

            if (index1 < 0 || index2 < 0)
            {
                return "";
            }
            //定位到前面的位置
            index1 = index1 + firstStr.Length;
            //判断要取的文本的长度
            index2 = index2 - index1;

            if (index1 < 0 || index2 < 0)
            {
                return "";
            }
            //取出文本
            return allStr.Substring(index1, index2);
        }

    }
}
