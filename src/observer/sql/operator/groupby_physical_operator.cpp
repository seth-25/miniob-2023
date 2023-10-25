//
// Created by seth on 2023/10/24.
//

#include "groupby_physical_operator.h"
RC GroupByPhysicalOperator::open(Trx *trx) { return RC::RECORD_EOF; }
RC GroupByPhysicalOperator::next() { return RC::RECORD_EOF; }
RC GroupByPhysicalOperator::close() { return RC::RECORD_EOF; }
Tuple *GroupByPhysicalOperator::current_tuple() { return nullptr; }
