1.项目概述
  该项目的名称为活动安排问题。
  该项目的目的为给定一组活动，每个活动都有一个开始时间和结束时间，目标是安排出一个最大数量的相互兼容的活动集合，即这些活动之间不会相互冲突
  该项目的功能为输出可安排的最大数量活动的集合。
2.文件说明
  此项目运用了贪心算法的思想，通过按照终止时间对活动进行排序，得出结果。
3.使用指南
  输入活动的个数，分别输入活动的开始时间和结束时间，可得出最大数量的相互兼容的活动集合。
4.示例
输入：
请输入活动个数：5
请输入各个活动的起始时间与结束时间：1 4 3 5 0 4 2 6 5 8
输出：
最大的相容活动集合为：3 5