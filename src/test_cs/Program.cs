// See https://aka.ms/new-console-template for more information
using System;
using System.Collections;

public enum Relationship
{ LessThan = -1, Equals = 0, GreaterThan = 1 }

class TestDecimal
{
  static void Main()
  {
    {

      decimal dec1t = new decimal(865371738, 1323190223, 575894324, true, 17);

      decimal dec1 = new decimal(-1, -1, -1, false, 0);
      decimal dec2 = new decimal(1, 0, 0, false, 0);
      decimal dec_add = dec2 + dec1;
      Console.WriteLine(dec_add);
      S21Decimal sdec_add = new S21Decimal(dec_add);
      sdec_add.printDecimal();
      (new S21Decimal(dec1t)).printDecimal();
    }
    //     {
    //       // dec_4.1: 1 16 1006090516 2063562674 1823452201: -1855909427250,1319019369835561
    //       // dec_4.2: 1 24 371183081 727547957 321316291: -6847,119302822797149863339459
    //       // add_4: 1 16 1006090520 825885434 4016760276: -1855909434097,2512047597807060
    // decimal deca = new decimal(2119662946, 82588543, 100609052, true, 15);
    //       decimal dec1 = new decimal(1823452201, 2063562674, 1006090516, true, 16);
    //       decimal dec2 = new decimal(321316291, 727547957, 371183081, true, 24);
    //       decimal dec_add = dec1 + dec2;
    //       Console.WriteLine(dec_add);
    //       S21Decimal sdec_add = new S21Decimal(dec_add);
    //       sdec_add.printDecimal();
    //       // decimal dec1_add = dec_add * 10M;
    //       // Console.WriteLine(dec1_add);
    //       S21Decimal sdec1_add = new S21Decimal(deca);
    //       sdec1_add.printDecimal();
    //     }
    // decimal dec1 = 36367.5364574M;
    // for (int i = 0; i < 15; i++)
    // {
    //   printTest(i);
    // }
    // print_add_check(0);
  }
  public static void print_head_check(int index)
  { }
  public static void print_add_check(int index)
  {
    Console.WriteLine("#test add {0}", index);
    bool sign1 = Convert.ToBoolean(S21Random.GetRandom(0, 2));
    byte exp1 = Convert.ToByte(S21Random.GetRandom(0, 29));
    S21Decimal dec1 = new S21Decimal(
      sign1,
      exp1,
      S21Random.GetRandom(0, Int32.MaxValue) / 10,
      S21Random.GetRandom(0, Int32.MaxValue) / 10,
      S21Random.GetRandom(0, Int32.MaxValue) / 10);
    Console.WriteLine("  s21_decimal dec1 = set_decimal({0}, {1}, {2}, {3}, {4});",
      dec1.bits[0],
      dec1.bits[1],
      dec1.bits[3],
      exp1,
      sign1);
    bool sign2 = Convert.ToBoolean(S21Random.GetRandom(0, 2));
    byte exp2 = Convert.ToByte(S21Random.GetRandom(0, 29));

    S21Decimal dec2 = new S21Decimal(
      sign2,
      exp2,
      S21Random.GetRandom(0, Int32.MaxValue) / 10,
      S21Random.GetRandom(0, Int32.MaxValue) / 10,
      S21Random.GetRandom(0, Int32.MaxValue) / 10);
    Console.WriteLine("  s21_decimal dec1 = set_decimal({0}, {1}, {2}, {3}, {4});",
      dec2.bits[0],
      dec2.bits[1],
      dec2.bits[3],
      exp2,
      sign2);

    S21Decimal dec = new S21Decimal(dec1.dec + dec2.dec);
    Console.WriteLine("  s21_decimal dec_add_ori = set_decimal({0}, {1}, {2}, {3}, {4});",
      dec.bits[0],
      dec.bits[1],
      dec.bits[3],
      dec.getExp(),
      dec.getSign());

    Console.WriteLine("  s21_decimal dec_add = {0};");
    Console.WriteLine("  s21_add(dec1, dec2, &dec_add);");
    Console.WriteLine("  char* s21_add = print_dec(dec_add);");
    Console.WriteLine("  char* ori_add = print_dec(origin_dec.add);");
    Console.WriteLine("  ck_assert_str_eq(s21_add, ori_add);");
    Console.WriteLine("  free(s21_add);");
    Console.WriteLine("  free(ori_add);");
  }
  public static void printTest(int index)
  {
    S21Decimal dec1 = new S21Decimal();
    Console.Write("dec_{0}.1: ", index);
    dec1.printDecimal();
    S21Decimal dec2 = new S21Decimal();
    Console.Write("dec_{0}.2: ", index);
    dec2.printDecimal();

    // // arithmetic--
    // sum--
    S21Decimal decAdd = S21Decimal.add(dec1, dec2);
    Console.Write("add_{0}: ", index);
    decAdd.printDecimal();
    // --sum

    // sub--
    S21Decimal decSub = S21Decimal.sub(dec1, dec2);
    Console.Write("sub_{0}: ", index);
    decSub.printDecimal();
    // --sub

    // mul--
    S21Decimal decMul = S21Decimal.mul(dec1, dec2);
    Console.Write("mul_{0}: ", index);
    decMul.printDecimal();
    // --mul

    // div--
    S21Decimal decDiv1 = S21Decimal.div(dec1, dec2);
    Console.Write("div_{0}_dec_{0}.1: ", index);
    decDiv1.printDecimal();
    S21Decimal decDiv2 = S21Decimal.div(dec2, dec1);
    Console.Write("div_{0}_dec_{0}.2: ", index);
    decDiv2.printDecimal();
    // --div

    // mod--
    S21Decimal decMod1 = S21Decimal.mod(dec1, dec2);
    Console.Write("mod_{0}_dec_{0}.1: ", index);
    decMod1.printDecimal();
    S21Decimal decMod2 = S21Decimal.mod(dec2, dec1);
    Console.Write("mod_{0}_dec_{0}.2: ", index);
    decMod2.printDecimal();
    // --mod

    // // --arithmetic

    // compare--
    Console.WriteLine("compare_1_{1}: {0}: dec_{1}.1 {2} dec_{1}.2", Decimal.Compare(dec1.dec, dec2.dec), index, (Relationship)Decimal.Compare(dec1.dec, dec2.dec));
    Console.WriteLine("compare_2_{1}: {0}: dec_{1}.2 {2} dec_{1}.1", Decimal.Compare(dec2.dec, dec1.dec), index, (Relationship)Decimal.Compare(dec2.dec, dec1.dec));
    // --compare

    // // other--

    // floor--
    Console.Write("floor_{0}_dec_{0}.1: ", index);
    (new S21Decimal(Decimal.Floor(dec1.dec))).printDecimal();
    Console.Write("floor_{0}_dec_{0}.2: ", index);
    (new S21Decimal(Decimal.Floor(dec2.dec))).printDecimal();
    // --floor

    // round--
    Console.Write("round_{0}_dec_{0}.1: ", index);
    (new S21Decimal(Decimal.Round(dec1.dec))).printDecimal();
    Console.Write("round_{0}_dec_{0}.2: ", index);
    (new S21Decimal(Decimal.Round(dec2.dec))).printDecimal();
    // --round

    // trunclucate--
    Console.Write("trunc_{0}_dec_{0}.1: ", index);
    (new S21Decimal(Decimal.Truncate(dec1.dec))).printDecimal();
    Console.Write("trunc_{0}_dec_{0}.2: ", index);
    (new S21Decimal(Decimal.Truncate(dec2.dec))).printDecimal();
    // --trunclucate

    // negate--
    Console.Write("negate_{0}_dec_{0}.1: ", index);
    (new S21Decimal(-dec1.dec)).printDecimal();
    Console.Write("negate_{0}_dec_{0}.2: ", index);
    (new S21Decimal(-dec2.dec)).printDecimal();
    // negate--

    // // --other

    // convert--
    {

      // int to dec--
      int num = Convert.ToInt32(S21Random.getRandomFloat() * Int32.MaxValue * Convert.ToSingle(Math.Pow(-1, S21Random.GetRandom(0, 2))));
      Console.Write("intToDec_{1}: {0} -> dec: ", num, index);
      (new S21Decimal(new decimal(num))).printDecimal();
      // --int to dec

      // dec to int--
      try
      {
        S21Decimal dec = new S21Decimal(new decimal(num));
        Console.WriteLine("decToInt_{6}: {0} {1} {2} {3} {4} -> {5}",
          Convert.ToByte(dec.sign),
          dec.getExp(),
          Convert.ToInt32(dec.bits[2]),
          Convert.ToInt32(dec.bits[1]),
          Convert.ToInt32(dec.bits[0]),
          Decimal.ToInt32(dec.dec),
          index);
      }
      catch (System.OverflowException e)
      {
        Console.WriteLine("decToInt_{1}: -2 exception: {0}", e.Message, index);
      }
      // --dec to int
    }

    {
      // float to dec--
      float f = Convert.ToSingle(Math.Pow(-1, S21Random.GetRandom(0, 2))) * S21Random.getRandomFloat() / Int32.MaxValue;
      try
      {
        S21Decimal dec = new S21Decimal(new decimal(f));
        Console.Write("floatToDec_{1}: {0} -> dec: ", f, index);
        (new S21Decimal(new decimal(f))).printDecimal();
      }
      catch (System.OverflowException e)
      {
        Console.WriteLine("floatToDec_{1}: -2 exception: {0}", e.Message, index);
      }
      // --float to dec

      // dec to float--
      {
        S21Decimal dec = new S21Decimal(new decimal(f));
        Console.WriteLine("decToFloat_{6}: {0} {1} {2} {3} {4} -> {5}",
          Convert.ToByte(dec.sign),
          dec.getExp(),
          Convert.ToInt32(dec.bits[2]),
          Convert.ToInt32(dec.bits[1]),
          Convert.ToInt32(dec.bits[0]),
          Decimal.ToSingle(dec.dec),
          index);
      }
      // --dec to float
    }
    //--convert
  }
  class S21Random
  {
    public static Random rand = new Random();
    public static float getRandomFloat()
    {
      return rand.NextSingle();
    }
    public static int GetRandom(int atNum, int toNum)
    {
      Random rand = new Random();
      int value = rand.Next(atNum, toNum);
      return value;
    }
  }
  class S21Decimal
  {
    public bool sign { set; get; }
    public byte exp { set; get; }
    public decimal dec;
    public int[] bits;

    public S21Decimal(bool sign, byte exp, Decimal dec)
    {
      this.sign = sign;
      this.exp = exp;
      bits = decimal.GetBits(dec);
      this.dec = new decimal(bits[0], bits[1], bits[2], sign, exp);
    }
    public S21Decimal()
    {
      sign = Convert.ToBoolean(S21Random.GetRandom(0, 2));
      exp = Convert.ToByte(S21Random.GetRandom(0, 29));
      dec = new decimal(S21Random.GetRandom(0, Int32.MaxValue) / 10, S21Random.GetRandom(0, Int32.MaxValue) / 10, S21Random.GetRandom(0, Int32.MaxValue / 10), sign, exp);
      bits = decimal.GetBits(dec);
    }
    public S21Decimal(bool sign, byte exp, int bitHigh, int bitMiddle, int bitLow)
    {
      this.sign = sign;
      this.exp = exp;
      dec = new decimal(bitLow, bitMiddle, bitHigh, sign, exp);
      bits = decimal.GetBits(dec);
    }
    public S21Decimal(Decimal dec)
    {
      bits = decimal.GetBits(dec);
      this.dec = dec;
      this.exp = this.getExp();
      this.sign = Convert.ToBoolean(this.getSign());
    }
    public static S21Decimal add(S21Decimal dec1, S21Decimal dec2)
    {
      return new S21Decimal(dec1.dec + dec2.dec);
    }
    public static S21Decimal sub(S21Decimal dec1, S21Decimal dec2)
    {
      return new S21Decimal(dec1.dec - dec2.dec);
    }
    public static S21Decimal mul(S21Decimal dec1, S21Decimal dec2)
    {
      decimal mul = new decimal(0);
      try
      {
        checked
        {
          mul = dec1.dec * dec2.dec;
        }
      }
      catch (OverflowException e)
      {
        Console.Write("mul: -2 exception: {0}", e.Message);
      }
      return new S21Decimal(mul);
    }
    public static S21Decimal div(S21Decimal dec1, S21Decimal dec2)
    {
      return new S21Decimal(dec1.dec / dec2.dec);
    }
    public static S21Decimal mod(S21Decimal dec1, S21Decimal dec2)
    {
      return new S21Decimal(dec1.dec % dec2.dec);
    }
    public void printDecimal()
    {
      Console.Write("{0} {1} {2} {3} {4}: ",
     Convert.ToString(Convert.ToByte(sign)),
     Convert.ToString(exp),
     Convert.ToString((uint)bits[2]),
     Convert.ToString((uint)bits[1]),
     Convert.ToString((uint)bits[0]));
      Console.Write("{0}\n", dec);
    }
    public byte getSign()
    {
      BitArray bitArray = new BitArray(new int[] { bits[3] });
      return Convert.ToByte(bitArray.Get(31));
    }
    public byte getExp()
    {
      BitArray bitArray = new BitArray(new int[] { bits[3] });
      BitArray expArray = new BitArray(8, false);
      for (int i = 16; i < 24; i++)
      {
        expArray.Set(i - 16, bitArray.Get(i));
      }
      return bitToExp(expArray);
    }
    static void WriteBits(BitArray bits)
    {
      foreach (bool b in bits)
        Console.Write(b ? 1 : 0);
      Console.WriteLine("\n");
    }
    private byte bitToExp(BitArray bitArray)
    {
      byte exp = 0;
      for (int i = 0; i < bitArray.Count; i++)
      {
        if (bitArray[i]) exp += Convert.ToByte(Math.Pow(2, i));
      }
      return exp;
    }
  }
}
